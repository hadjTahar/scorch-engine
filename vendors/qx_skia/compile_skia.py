import argparse
import platform
import shutil
import subprocess
import sys
from pathlib import Path


def run(command, cwd):
    print(f"\n> {' '.join(map(str, command))}")
    subprocess.run(command, cwd=cwd, check=True)


def main():
    parser = argparse.ArgumentParser(
        description="Configure and build Skia."
    )

    parser.add_argument(
        "skia_gn_args",
        help="Path/name of the GN args file or directory containing args.gn."
    )

    args = parser.parse_args()

    # ------------------------------------------------------------------
    # Directories
    # ------------------------------------------------------------------

    script_dir = Path(__file__).resolve()
    skia_dir = (script_dir.parent / ".").resolve()

    if not skia_dir.is_dir():
        raise RuntimeError(f"Skia directory not found: {skia_dir}")

    # ------------------------------------------------------------------
    # Find GN executable
    # ------------------------------------------------------------------

    system = platform.system()

    if system == "Windows":
        gn = skia_dir / "bin" / "gn.exe"
    else:
        gn = skia_dir / "bin" / "gn"

    if not gn.is_file():
        raise RuntimeError(f"GN executable not found: {gn}")

    # ------------------------------------------------------------------
    # Resolve skia_gn_args
    # ------------------------------------------------------------------

    gn_args_source = Path(args.skia_gn_args)

    # Allow the argument to be relative to the directory containing
    # compile_skia.py.
    if not gn_args_source.is_absolute():
        gn_args_source = (script_dir.parent / gn_args_source).resolve()

    # If a directory was provided, use args.gn inside it.
    if gn_args_source.is_dir():
        gn_args_file = gn_args_source / "args.gn"
    else:
        gn_args_file = gn_args_source

    if not gn_args_file.is_file():
        raise RuntimeError(
            f"GN args file not found: {gn_args_file}"
        )

    # ------------------------------------------------------------------
    # Output directory
    #
    # Example:
    #
    #   skia_gn_args = "skia_gn_args"
    #
    # produces:
    #
    #   skia/qx_out/skia_gn_args
    # ------------------------------------------------------------------

    output_name = gn_args_source.name.removesuffix(".args")

    output_dir = skia_dir / "qx_out" / output_name
    output_args_file = output_dir / "args.gn"

    # Path relative to skia_dir.
    #
    # This is important because it makes the command equivalent to:
    #
    #   .\bin\gn.exe gen qx_out\skia_gn_args
    #
    gn_output = output_dir.relative_to(skia_dir)

    # ------------------------------------------------------------------
    # First GN generation
    # ------------------------------------------------------------------

    output_dir.mkdir(parents=True, exist_ok=True)

    run(
        [str(gn), "gen", str(gn_output)],
        cwd=skia_dir,
    )

    # ------------------------------------------------------------------
    # Copy GN arguments
    # ------------------------------------------------------------------

    print("\nCopying GN args:")
    print(f"  From: {gn_args_file}")
    print(f"  To:   {output_args_file}")

    shutil.copyfile(
        gn_args_file,
        output_args_file,
    )

    # ------------------------------------------------------------------
    # Reconfigure GN with the copied args
    # ------------------------------------------------------------------

    run(
        [str(gn), "gen", str(gn_output)],
        cwd=skia_dir,
    )

    # ------------------------------------------------------------------
    # Build Skia
    # ------------------------------------------------------------------

    ninja = shutil.which("ninja")

    if ninja is None:
        raise RuntimeError(
            "ninja was not found in PATH."
        )

    run(
        [ninja, "-C", str(gn_output), "skia"],
        cwd=skia_dir,
    )

    # ------------------------------------------------------------------
    # Copy generated Skia library
    # ------------------------------------------------------------------

    if system == "Windows":
        library_name = "skia.lib"
    elif system in ("Linux", "Darwin"):
        library_name = "libskia.a"
    else:
        raise RuntimeError(
            f"Unsupported platform: {system}"
        )

    generated_library = output_dir / library_name

    if not generated_library.is_file():
        raise RuntimeError(
            f"Generated Skia library not found: {generated_library}"
        )

    lib_dir = skia_dir / "qx_out" / "lib"
    lib_dir.mkdir(parents=True, exist_ok=True)

    destination_library = lib_dir / library_name

    print("\nCopying Skia library:")
    print(f"  From: {generated_library}")
    print(f"  To:   {destination_library}")

    shutil.copy2(
        generated_library,
        destination_library,
    )

    # ------------------------------------------------------------------
    # Done
    # ------------------------------------------------------------------

    print("\nSkia build completed successfully.")
    print(f"Output directory: {output_dir}")
    print(f"Library: {destination_library}")


if __name__ == "__main__":
    try:
        main()
    except subprocess.CalledProcessError as e:
        print(
            f"\nCommand failed with exit code {e.returncode}.",
            file=sys.stderr,
        )
        sys.exit(e.returncode)
    except Exception as e:
        print(f"\nError: {e}", file=sys.stderr)
        sys.exit(1)