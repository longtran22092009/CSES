# #!/bin/bash
# shopt -s globstar nullglob

# read -p "Enter path to your code folder: " codepath

# # Check if directory exists
# if [ ! -d "$codepath" ]; then
#     echo "❌ Error: Directory does not exist: $codepath"
#     exit 1
# fi

# cd "$codepath"

# for file in **/*.cpp; do
#     base=$(basename "$file")
#     dir=$(dirname "$file")

#     if [[ "$base" =~ ^([0-9]+)\.(.*\.cpp)$ ]]; then
#         id="${BASH_REMATCH[1]}"
#         name="${BASH_REMATCH[2]}"
#         newid=$(printf "%03d" "$id")
#         newname="${newid}.${name}"

#         # Only rename if the name changes
#         if [[ "$base" != "$newname" ]]; then
#             echo "Renaming: $file -> $dir/$newname"
#             mv "$file" "$dir/$newname"
#         fi
#     fi
# done

#!/bin/bash
shopt -s globstar nullglob

# === INPUT ===
read -p "Enter path to your code folder: " codepath
read -p "Do you want to insert a new file? (y/n): " insert_flag

if [ ! -d "$codepath" ]; then
    echo "❌ Directory does not exist."
    exit 1
fi

cd "$codepath" || exit 1

# === STEP 1: RENAME ALL FILES TO 3-DIGIT FORMAT ===
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

# === STEP 2: INSERT NEW FILE IF REQUESTED ===
if [[ "$insert_flag" == "y" ]]; then
    read -p "Enter position to insert at (1-based): " insert_pos
    read -p "Enter new file name (e.g. Binary Search.cpp): " new_name

    # Sort all files by number
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

    # Create new file
    insert_id=$(printf "%03d" "$insert_pos")
    echo "// $new_name" > "$insert_id. $new_name"
    echo "✅ Inserted: $insert_id. $new_name"
fi

echo "✅ Done renaming and optional insertion."
