import xml.etree.ElementTree as ET
from googletrans import Translator

# Đường dẫn file đầu vào và đầu ra
INPUT_FILE = 'qgc_source_bg_BG.ts'
OUTPUT_FILE = 'qgc_source_vi_VN.ts'

# Khởi tạo translator
translator = Translator()

# Đọc và parse file XML
tree = ET.parse(INPUT_FILE)
root = tree.getroot()

# Lặp qua từng phần tử <message> để dịch nội dung trong <source>
for message in root.findall(".//message"):
    source = message.find("source")
    translation = message.find("translation")

    if source is not None and source.text:
        english_text = source.text.strip()

        # Nếu translation chưa có hoặc là unfinished thì dịch
        if translation is not None and (
            translation.attrib.get("type") == "unfinished" or not translation.text.strip()
        ):
            try:
                # Dịch sang tiếng Việt
                translated_text = translator.translate(english_text, src="en", dest="vi").text
                print(f"Đang dịch: {english_text} -> {translated_text}")
                # Ghi đè nội dung dịch mới
                translation.text = translated_text
                # Xoá thuộc tính "unfinished" nếu có
                if "type" in translation.attrib:
                    del translation.attrib["type"]

            except Exception as e:
                print(f"Lỗi khi dịch: {english_text} - {e}")
    else:
        continue

# Ghi file đã được dịch ra
tree.write(OUTPUT_FILE, encoding="utf-8", xml_declaration=True)
print(f"✅ File đã được dịch lưu vào: {OUTPUT_FILE}")
