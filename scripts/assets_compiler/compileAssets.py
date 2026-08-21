import sys
import os
from pathlib import Path
import shutil
import subprocess

import files2Cpp


def getAssetsPairs(folder_path: str, prefix: str):
    pairs = []
    folder_path = os.path.abspath(folder_path).replace(os.sep, "/")  # Ensure absolute path with forward slashes
    
    for root, _, files in os.walk(folder_path):
        root = root.replace(os.sep, "/")  # Ensure root uses forward slashes
        for file in files:
            full_path = os.path.join(root, file).replace(os.sep, "/")
            local_path = os.path.relpath(full_path, folder_path).replace(os.sep, "/")  # Local relative path with forward slashes
            pairs.append((full_path, f"{prefix}{local_path}"))
    
    return pairs


def delete_folder(folder_path):
    path = Path(folder_path)

    # Check if the path exists AND is actually a directory
    if path.exists() and path.is_dir():
        shutil.rmtree(path)
        print(f"Successfully deleted: {folder_path}")
    elif path.exists() and not path.is_dir():
        print(f"Error: {folder_path} is a file, not a folder.")
    else:
        print(f"Skip: {folder_path} does not exist.")

def main():
    print( "-----------------------------------------------------" )

    qxSrcDir      = sys.argv[1]
    appSrcDir     = sys.argv[2]
    compileAssets = (sys.argv[3] == "ON") or (sys.argv[3] == "YES")
    if( not compileAssets ):
        delete_folder("compiled_assets")
        return


    print( "+++++++" )
    print( "qxSrcDir : "  + qxSrcDir )
    print( "appSrcDir : "  + appSrcDir )
    print( compileAssets )
    assetsPairs   = getAssetsPairs(appSrcDir + "/assets", ":/"  )
    print( "-----------------------------------------------------" )
    print( assetsPairs )


    files2Cpp.compile( assetsPairs, "compiled_assets")



if __name__ == "__main__":
    sys.exit(main()) # Calls the main function and exits with its return code



