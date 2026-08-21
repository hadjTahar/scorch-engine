import subprocess
import os

skia_dir = os.path.abspath( "skia" )

subprocess.run(
    ["python", "tools/git-sync-deps", "--verbose"],
    cwd=skia_dir,
    check=True
)

subprocess.run(
    ["python", "tools/git-sync-deps", "--verbose"],
    cwd=skia_dir,
    check=True
)