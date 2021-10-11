import math
key = input(
    "Enter keyword text (Contains unique letters only): ").lower().replace(" ", "")
plain_text = input(
    "Enter plain text (Letters only): ").lower().replace(" ", "")

len_key = len(key)
len_plain = len(plain_text)
row = int(math.ceil(len_plain / len_key))
matrix = [['X']*len_key for i in range(row)]

# Encryption
t = 0
for r in range(row):
    for c, ch in enumerate(plain_text[t: t + len_key]):
        matrix[r][c] = ch
    t += len_key

# to make alphabetically order of chars
sort_order = sorted([(ch, i) for i, ch in enumerate(key)])

cipher_text = ''
for ch, c in sort_order:
    for r in range(row):
        cipher_text += matrix[r][c]

print("Encryption")
print("Plain text is :", plain_text)
print("Cipher text is:", cipher_text)

# Decryption
matrix_new = [['X']*len_key for i in range(row)]
# to make original key order when we know keyword
key_order = [key.index(ch) for ch in sorted(list(key))]

t = 0
for c in key_order:
    for r, ch in enumerate(cipher_text[t: t + row]):
        matrix_new[r][c] = ch
    t += row

p_text = ''
for r in range(row):
    for c in range(len_key):
        p_text += matrix_new[r][c] if matrix_new[r][c] != 'X' else ''

print("Decryption")
print("Cipher text is:", cipher_text)
print("Plain text is :", p_text)
