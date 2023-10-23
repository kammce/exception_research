#!/bin/bash

CHECK_EXPR="\(\!scoped_result\|\!result\)"

conan build test_suite -pr test_suite/baremetal.profile

function get_text_data_bss() {
  input=$1  # Taking the input as a string variable
  # Extracting the second, third, and fourth numbers from the second line
  other_numbers=$(echo "$input" | grep -Eo '[0-9]+[[:space:]]+[0-9]+[[:space:]]+[0-9]+' | tr -s '[:space:]' ',' )
  # Combining the numbers and printing the result
  echo "$first_number,$other_numbers"
}

function trim() {
  echo "$1" | awk '{$1=$1; print}'
}

function get_sample_number() {
  number=$(echo "$filename" | awk -F'_' '{print $2}')
  echo "$number"
}

echo "sample#,except.text,except.data,except.bss,reserved,result.text,result.data,result.bss,result.checks"
for full_file in test_suite/except_*.cpp; do
    filename=$(basename -- "$full_file")
    extension="${filename##*.}"
    filename="${filename%.*}"
    sample_number=$(get_sample_number "$filename")
    echo -n "$sample_number"

    size_info=$(arm-none-eabi-size \
      test_suite/build/MinSizeRel/except_$sample_number.elf)
    csv=$(get_text_data_bss "$size_info")
    echo -n "$csv"
    echo -n "0"
    size_info=$(arm-none-eabi-size \
      test_suite/build/MinSizeRel/result_$sample_number.elf)
    csv=$(get_text_data_bss "$size_info")
    echo -n $csv
    check_count_str=$(grep -op "$CHECK_EXPR" \
      "test_suite/result_$sample_number.cpp" | wc -l)
    echo "$(trim $check_count_str)"
done
