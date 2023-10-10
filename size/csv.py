#!/usr/bin/python
#
# Copyright 2023 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import argparse
from pathlib import Path

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-f", "--file",
                        help="size file to convert into CSV",
                        default="file_sizes.txt",
                        type=Path)
    args = parser.parse_args()
    file_name = args.file
    data = Path(file_name).read_text()
    # Split data by lines and skip the header
    lines = data.strip().split('\n')[1:]

    # Extract relevant details from each line and group by file number
    grouped_files = {}
    for line in lines:
        text, data, bss, dec, hex_val, filename = line.split()
        base_name = filename.split('/')[-1]
        name, ext = base_name.split('.')
        file_type, file_num = name.split('_')
        file_num = int(file_num)
        grouped_files.setdefault(file_num, {})[file_type] = (
            text, data, bss, dec, hex_val)

    # Write the results to a CSV
    csv_output = "text_except,data_except,bss_except,dec_except,hex_except,filename_except,text_result,data_result,bss_result,dec_result,hex_result,filename_result\n"
    for file_num in sorted(grouped_files.keys()):
        except_data = grouped_files[file_num]['except']
        result_data = grouped_files[file_num]['result']
        csv_output += ','.join(except_data) + f",except_{file_num}.elf," + ','.join(
            result_data) + f",result_{file_num}.elf\n"

    # Print or save csv_output to a file
    print(csv_output)
