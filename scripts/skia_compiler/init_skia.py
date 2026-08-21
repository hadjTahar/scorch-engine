import subprocess
import os

# Go to ../../vendors/skia relative to this script's directory
script_dir = os.path.dirname(os.path.abspath(__file__))
skia_dir = os.path.abspath(os.path.join(script_dir, "../../vendors/skia"))

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