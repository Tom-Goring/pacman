MICROBIT_PATH = /media/tom/MICROBIT

SOURCE_FILES += \
    source/main.cpp

OUTPUT_FILE = build/bbc-microbit-classic-gcc/source/pacman-combined.hex

run: ${OUTPUT_FILE}
	cp ${OUTPUT_FILE} ${MICROBIT_PATH}

${OUTPUT_FILE}: ${SOURCE_FILES}
	yt target bbc-microbit-classic-gcc
	yt build