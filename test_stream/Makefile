gen:
	python3 mavlink/pymavlink/tools/mavgen.py   --lang=Python   --wire-protocol=2.0   --output=generated/include/mavlink/gimbal   gimbal.xml
gen-c:
	python3 mavlink/pymavlink/tools/mavgen.py   --lang=C   --wire-protocol=2.0   --output=../generated/include/mavlink/gimbal   gimbal.xml

.PHONY: gen gen-c