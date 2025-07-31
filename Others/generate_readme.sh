#!/bin/bash
shopt -s globstar nullglob

read -p "Enter path to your code folder [default: current folder]: " codepath
codepath="${codepath:-.}"
cd "$codepath" || exit 1

output_file="README.md"
echo "# 🗂️ Problem List" > "$output_file"
echo "" >> "$output_file"

for section_path in */; do
    section_name=$(basename "$section_path")

    # Skip the "Others" folder
    if [[ "$section_name" == "Others" ]]; then
        continue
    fi

    readable_section=$(echo "$section_name" | sed 's/_/ /g')

    echo "## 🔹 $readable_section" >> "$output_file"
    echo "" >> "$output_file"
    echo "| ID  | Problem Name | File Link |" >> "$output_file"
    echo "|-----|--------------|-----------|" >> "$output_file"

    for file in "$section_path"*.cpp; do
        filename=$(basename "$file")

        if [[ "$filename" =~ ^([0-9]{3})\.(.*)\.cpp$ ]]; then
            id="${BASH_REMATCH[1]}"
            name="${BASH_REMATCH[2]}"
            name_cleaned=$(echo "$name" | sed 's/_/ /g')
            filepath="$section_name/$filename"
            encoded_link=$(echo "$filepath" | sed 's/ /%20/g')
            echo "| $id | $name_cleaned | [$filename]($encoded_link) |" >> "$output_file"
        fi
    done

    echo "" >> "$output_file"
done

echo "✅ README.md created at: $codepath/README.md"
