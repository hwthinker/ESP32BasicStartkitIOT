#!/bin/bash

# Nama file output
OUTPUT_FILE="combined.md"

# Hapus file output jika sudah ada sebelumnya
if [ -f "$OUTPUT_FILE" ]; then
    rm "$OUTPUT_FILE"
fi

# Loop semua file *.md secara berurutan
for file in $(ls *.md | sort -V); do
    echo "Menggabungkan $file..."
    cat "$file" >> "$OUTPUT_FILE"
    echo -e "\n\n" >> "$OUTPUT_FILE" # Tambahkan baris kosong antara file
done

echo "Semua file .md berhasil digabungkan menjadi $OUTPUT_FILE"

