ex1_text = "Nd Dhy. A dcmgv yk ccob xsieewa svptdwn os ptp Kqg, url gz wazwry vaffu jj t mgzogk tsi os xyextrm lmb hildcmzu. B plsgp plpz oq npw dci Otikigkb usklxc.Egi ahr lrdrd zh g rcr qg wvox zwx hglpsqzw bxrunubydo os wpextrm cgb cik?"

## encrypt key with Caesar cipher
def caesar_encrypt(text: str, shift: int) -> str:
    return ''.join([chr((ord(i) + shift - ord('A')) % 26 + ord('A')) for i in text])
    
def caesar_decrypt(encrypted_text: str, shift: int) -> str:
    return ''.join([chr((ord(i) - shift + ord('Z') + 1) % 26 + ord('A')) for i in encrypted_text])

def vig_encrypt(text: str, key: str) -> str:   
    encrypted_text = ''
    for i in range(len(text)):
        encrypted_text += caesar_encrypt(text[i], ord(key[i % len(key)]) - ord('A'))
        
    return encrypted_text

def vig_decrypt(encrypted_text: str, key: str) -> str:
    decrypted_text = ''
    offset = 0 ## pointer offset to account for punctuation and whitespace
    for i in range(len(encrypted_text)):
        if(not encrypted_text[i].isalpha()):
            decrypted_text += encrypted_text[i]
            offset += 1
        else:
            decrypted_text += caesar_decrypt(encrypted_text[i], ord(key[(i - offset) % len(key)]) - ord('A'))
        
    return decrypted_text

if(__name__ == "__main__"):   
    ex1_key = "CRYPTOGRAPHY" 
    enkey = caesar_encrypt(ex1_key, 4)
    decrypted_text = vig_decrypt(ex1_text.upper(), enkey)
    print("shift: {}".format(4))
    print(decrypted_text)
    