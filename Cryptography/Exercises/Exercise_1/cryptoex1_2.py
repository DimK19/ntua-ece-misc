from cryptoex1 import caesar_encrypt, vig_encrypt, vig_decrypt

answer = "HI ALICE. WE MUST USE A KEY OF LENGTH EQUAL TO THAT OF THE MESSAGE, THAT IS, A ONE TIME PAD"
key = "CRYPTOGRAPHY"

enkey = caesar_encrypt(key, 14)

print(vig_encrypt(answer, enkey))
print(vig_decrypt(vig_encrypt(answer, enkey), enkey))

## XNFDSKWJVWRQJRGVAVOXSWVFAJKWVHNQSQBFXYQTBCFYHROFXFFWVHNYVHOYUXEDNGZYHKVFJNEIACNTBHOFYRQWWCX
