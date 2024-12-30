#!/bin/bash

# Create temporary directory
mkdir -p temp

# Create cover page
cat > temp/cover.md << 'EOF'
\begin{titlepage}
\begin{center}
\vspace*{3cm}
{\Huge\bfseries Memulai Belajar ESP32\par}
\vspace{2cm}
\includegraphics[width=0.7\textwidth]{gambar.png}
\end{center}
\end{titlepage}
\newpage
EOF

# Create license page
cat > temp/license.md << 'EOF'
\newpage
\thispagestyle{empty}
\vspace*{2cm}

**Lisensi Dokumen:**

Copyright © 2021 by Akhmad Hendriawan

Seluruh dokumen ini dapat digunakan dan disebarkan secara bebas untuk tujuan bukan
komersial (nonprofit), dengan syarat tidak menghapus atau merubah atribut penulis dan
pernyataan copyright yang disertakan dalam setiap dokumen. Tidak diperbolehkan melakukan
penghapusan atau perubahan atribut penulis dan pernyataan copyright yang disertakan dalam
setiap dokumen.

\newpage
EOF

# Combine all content
cat temp/cover.md temp/license.md > temp/combined.md
echo "\newpage" >> temp/combined.md
echo "\tableofcontents" >> temp/combined.md
echo "\newpage" >> temp/combined.md
echo "\listoffigures" >> temp/combined.md
echo "\newpage" >> temp/combined.md
cat mybook.md >> temp/combined.md

# Convert to PDF using pandoc
pandoc \
  --pdf-engine=xelatex \
  --toc \
  --toc-depth=5 \
  --number-sections \
  -f markdown+raw_tex \
  --include-in-header=header.tex \
  --metadata-file=metadata.yaml \
  -o output.pdf \
  temp/combined.md

# Clean up
rm -r temp
