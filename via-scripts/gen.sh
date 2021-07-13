qmk multibuild -km via -j 8
find . -name "*.hex" -exec mv '{}' ./firmware/ \;
find . -name "*.bin" -exec mv '{}' ./firmware/ \;
zip -r firmware.zip firmware
curl --upload-file ./firmware.zip https://transfer.sh/firmware.zip
