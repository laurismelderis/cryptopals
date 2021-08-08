from nostril import nonsense

# Requirement
# git clone https://github.com/casics/nostril.git
# cd nostril
# sudo python3 -m pip install .


with open("./out.txt", 'r', encoding="utf8", errors="ignore") as f:
    decodedXORMessages = f.readlines();

for message in decodedXORMessages:
    try:
        if not nonsense(message):
            print(message)
    except:
        pass
