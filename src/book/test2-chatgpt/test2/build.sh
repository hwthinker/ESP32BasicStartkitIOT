#!/bin/bash

# Install required packages
sudo apt install -y texlive-latex-base texlive-fonts-recommended \
    texlive-latex-extra texlive-lang-other pandoc texlive-xetex \
    fonts-dejavu

# Create license text
cat > license.md << EOL
# Lisensi Dokumen

Copyright © 2021 by Akhmad Hendriawan

Seluruh dokumen ini dapat digunakan dan disebarkan secara bebas untuk tujuan bukan
komersial (nonprofit), dengan syarat tidak menghapus atau merubah atribut penulis dan
pernyataan copyright yang disertakan dalam setiap dokumen. Tidak diperbolehkan melakukan
penghapusan atau perubahan atribut penulis dan pernyataan copyright pada setiap dokumen.
EOL

# Create title page
cat > title.md << EOL
![](gambar.png)

# Memulai Belajar ESP32
EOL

# Create post-toc page break
cat > post_toc.tex << EOL
\newpage
\listoffigures
\newpage
EOL

# Combine all content
cat title.md license.md mybook.md > combined.md

# Convert to PDF using XeLaTeX
pandoc combined.md \
  -f markdown \
  -t pdf \
  --metadata-file=metadata.yaml \
  --pdf-engine=xelatex \
  -V geometry:margin=2.5cm \
  --include-after-body=post_toc.tex \
  --standalone \
  -o output.pdf

# Clean up temporary files
rm title.md license.md combined.md post_toc.tex
