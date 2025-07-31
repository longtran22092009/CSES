#!/bin/bash
shopt -s globstar nullglob

read -p "Enter path to your code folder: " codepath

if [ ! -d "$codepath" ]; then
    echo "❌ Directory does not exist."
    exit 1
fi

cd "$codepath" || exit 1

# === STEP 1: RENAME ALL FILES TO 3-DIGIT FORMAT ===
echo "🔄 Renaming all .cpp files to 3-digit format..."
for file in **/*.cpp; do
    base=$(basename "$file")
    dir=$(dirname "$file")

    if [[ "$base" =~ ^([0-9]+)\.(.*\.cpp)$ ]]; then
        id="${BASH_REMATCH[1]}"
        name="${BASH_REMATCH[2]}"
        newid=$(printf "%03d" "$id")
        newname="${newid}.${name}"

        if [[ "$base" != "$newname" ]]; then
            mv "$file" "$dir/$newname"
        fi
    fi
done
echo "✅ Renaming complete."

# === STEP 2: OPERATION CHOICE ===
echo "Choose an operation:"
echo "1. Insert a new file"
echo "2. Delete a file"
echo "3. Do nothing else"
read -p "Enter your choice (1/2/3): " choice

# === STEP 3A: INSERT NEW FILE ===
if [[ "$choice" == "1" ]]; then
    read -p "Enter position to insert at (1-based): " insert_pos
    read -p "Enter new file name (e.g. Binary Search.cpp): " new_name

    mapfile -t files < <(find . -type f -name '*.cpp' | sort)

    for ((i=${#files[@]}-1; i>=insert_pos-1; i--)); do
        oldfile="${files[i]}"
        base=$(basename "$oldfile")
        dir=$(dirname "$oldfile")

        if [[ "$base" =~ ^([0-9]+)\.(.*\.cpp)$ ]]; then
            old_id="${BASH_REMATCH[1]}"
            rest="${BASH_REMATCH[2]}"
            new_id=$(printf "%03d" "$((10#$old_id + 1))")
            mv "$oldfile" "$dir/$new_id.$rest"
        fi
    done

    new_id=$(printf "%03d" "$insert_pos")
    echo "// $new_name" > "$new_id. $new_name"
    echo "✅ Inserted: $new_id. $new_name"

# === STEP 3B: DELETE FILE ===
elif [[ "$choice" == "2" ]]; then
    read -p "Enter position to delete (1-based): " del_pos

    mapfile -t files < <(find . -type f -name '*.cpp' | sort)

    if (( del_pos < 1 || del_pos > ${#files[@]} )); then
        echo "❌ Invalid delete position"
        exit 1
    fi

    del_file="${files[del_pos-1]}"
    echo "🗑️  Deleting: $del_file"
    rm "$del_file"

    for ((i=del_pos; i<${#files[@]}; i++)); do
        oldfile="${files[i]}"
        base=$(basename "$oldfile")
        dir=$(dirname "$oldfile")

        if [[ "$base" =~ ^([0-9]+)\.(.*\.cpp)$ ]]; then
            old_id="${BASH_REMATCH[1]}"
            name="${BASH_REMATCH[2]}"
            new_id=$(printf "%03d" "$((10#$old_id - 1))")
            newname="$new_id.$name"
            mv "$oldfile" "$dir/$newname"
            echo "➡️  Shifted: $oldfile → $dir/$newname"
        fi
    done
    echo "✅ Deletion and shift complete."

else
    echo "👍 No insertion or deletion performed."
fi

echo "🎉 All operations completed."