#!/bin/bash
shopt -s globstar nullglob

read -p "Enter path to your code folder: " codepath
cd "$codepath" || exit 1

output_file="README.md"
echo "# 🗂️ Problem List" > "$output_file"
echo "" >> "$output_file"
echo "| ID   | Problem Name | Estimated Rating | File Link |" >> "$output_file"
echo "|------|--------------|------------------|-----------|" >> "$output_file"

for file in **/*.cpp; do
    base=$(basename "$file")
    if [[ "$base" =~ ^([0-9]{3})\.(.*)\.cpp$ ]]; then
        id="${BASH_REMATCH[1]}"
        name="${BASH_REMATCH[2]}"
        clean_name=$(echo "$name" | sed 's/_/ /g')
        encoded=$(printf "%s" "$base" | sed 's/ /%20/g')
        echo "| $id | $clean_name | ??? | [$base]($encoded) |" >> "$output_file"
    fi
done

echo "✅ README.md created in: $codepath/README.md"
