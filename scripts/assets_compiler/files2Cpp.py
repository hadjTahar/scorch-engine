import hashlib
import os
from pathlib import Path
import ast
import shutil

HEADER_TEMPLATE = """#pragma once
#include <array>

namespace Qx::prv {{

struct {struct_name}
{{
    static const std::array<unsigned char, {size}> AssetsData;
}};

}} // namespace Qx::prv
"""

SOURCE_TEMPLATE = """#include "{header_file}"

namespace Qx::prv {{

const std::array<unsigned char, {size}> {struct_name}::AssetsData = {{ {data} }};

}} // namespace Qx::prv
"""

def generate_cpp_files(input_file, output_folder):
    # Read the file content
    with open(input_file, 'rb') as f:
        content = f.read()

    # Hash the file name to derive the struct name
    # file_name = Path(input_file).name
    hashed_name = hashlib.sha256(input_file.encode()).hexdigest()[:10]
    struct_name = f"qx_{hashed_name}"

    # Convert file content to hex format
    hex_data = ", ".join(f"0x{byte:02X}" for byte in content)

    # Generate sizes
    size = len(content)

    # Generate header and source file content
    header_content = HEADER_TEMPLATE.format(struct_name=struct_name, size=size)
    source_content = SOURCE_TEMPLATE.format(
        header_file=f"{struct_name}.h",
        struct_name=struct_name,
        size=size,
        data=hex_data
    )

    # Ensure the output folder exists
    os.makedirs(output_folder, exist_ok=True)

    # Write to files
    struct_name = struct_name.lower()
    header_file = os.path.join(output_folder, f"{struct_name}.h")
    source_file = os.path.join(output_folder, f"{struct_name}.cpp")

    with open(header_file, 'w') as hf:
        hf.write(header_content)

    with open(source_file, 'w') as sf:
        sf.write(source_content)

    print(f"Generated files: {header_file}, {source_file}")


def compile( file_key_pairs, output_folder):
    shutil.rmtree(output_folder, ignore_errors=True)
    os.makedirs(output_folder, exist_ok=True)
    includes = []
    map_entries = []

    for file, key_name in file_key_pairs:
        generate_cpp_files(file, output_folder)

        # Generate struct name based on the file name
        # file_name = Path(file).name
        hashed_name = hashlib.sha256(file.encode()).hexdigest()[:10]
        struct_name = f"Qx_{hashed_name}".lower()

        includes.append(f"#include \"{struct_name}.h\"")
        map_entries.append(f"    {{ \"{key_name}\", x_dataSpan(Qx::prv::{struct_name}::AssetsData) }}")

    # Create the compiled_assets.h file
    assets_header = output_folder + "/compiled_assets.h"
    with open(assets_header, 'w') as ah:
        ah.write("#pragma once\n")
        ah.write("\n".join(includes))
        ah.write("\n\n#include <map>\n#include <string>\n#include <misc/defs.h>\n\nnamespace Qx::prv {\n\n")
        ah.write("static const std::map<std::string, const x_dataSpan> CompiledDataMap = {\n")
        ah.write(",\n".join(map_entries))
        ah.write("\n};\n\n")
        ah.write("} // namespace Qx::prv\n")

    print(f"Generated assets header: {assets_header}")

