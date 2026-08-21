import os
import sys
import subprocess
from pathlib import Path

def compile_mats(search_dir, matc_path):
    search_path = Path(search_dir)
    matc_executable = Path(matc_path)

    # Validate search directory
    if not search_path.exists():
        print(f"Error: The directory '{search_path}' does not exist.")
        return
        
    # Validate matc executable (must be an actual file, not a directory)
    if not matc_executable.exists() or not matc_executable.is_file():
        print(f"Error: Could not find the 'matc.exe' file at '{matc_executable}'.")
        print("Please ensure MATC_PATH points directly to the matc.exe file (e.g., r'C:/filament/bin/matc.exe').")
        return

    # Find all .mat files recursively
    mat_files = list(search_path.glob("**/*.mat"))

    if not mat_files:
        print(f"No '.mat' files found in '{search_path}' or its subdirectories.")
        return

    print(f"Found {len(mat_files)} material file(s). Starting compilation...\n")

    success_count = 0
    fail_count = 0

    for mat_file in mat_files:
        # Define output path (replaces .mat extension with .filamat)
        output_file = mat_file.with_suffix(".filamat")
        
        # Build the matc command
        cmd = [
            str(matc_executable.resolve()),
            "-o", str(output_file.resolve()),
            str(mat_file.resolve())
        ]

        print(f"Compiling: {mat_file.relative_to(search_path)}")
        
        try:
            # Execute the compilation process
            result = subprocess.run(cmd, capture_output=True, text=True, check=True)
            print(f"  -> Success: {output_file.name}")
            success_count += 1
        except subprocess.CalledProcessError as e:
            print(f"  -> Failed to compile: {mat_file.name}")
            print(f"  -> Error output:\n{e.stderr.strip()}")
            fail_count += 1
        print("-" * 40)

    print("\nCompilation Summary:")
    print(f"  Total processed : {len(mat_files)}")
    print(f"  Successful      : {success_count}")
    print(f"  Failed          : {fail_count}")

if __name__ == "__main__":
    # --- CONFIGURATION ---
    # Change these paths to fit your project layout or pass them via CLI
    TARGET_DIRECTORY = "../../modules/examples_3d/rotating_cube/assets/"      # Folder to search recursively for *.mat files
    
    # Path to your matc binary (e.g., "matc" if it's in your system PATH, 
    # or an explicit path like "./filament/bin/matc.exe" on Windows)
    MATC_PATH = "D:/builds/build/quick_graphics/x86_windows_msvc2026_pe_64bit-Release/vendors/filament_build/tools/matc/matc.exe"
    
    compile_mats(TARGET_DIRECTORY, MATC_PATH)