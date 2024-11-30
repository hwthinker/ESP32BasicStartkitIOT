pandoc combined.md -o output.pdf \
--pdf-engine=xelatex \
--toc --toc-depth=4 \
-V title="ESP32 Basic Starter Kit Tutorial" \
-V author="HwThinker" \
-V date="30-11-2024" \
-V "toc-title=Daftar Isi" \
-H header.tex \
-V geometry:margin=1in \
--top-level-division=chapter \
-V sectionbreak=true \
-V lof=true

