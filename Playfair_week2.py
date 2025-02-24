import string

# Tạo bảng Playfair
def create_playfair_table(key):
    key = ''.join(sorted(set(key), key=lambda x: key.index(x)))  # loại bỏ ký tự trùng
    key = key.replace('j', 'i')  # quy định rằng 'j' là 'i'
    alphabet = string.ascii_lowercase.replace('j', '')  # bỏ 'j' ra khỏi bảng chữ cái

    table = key + ''.join([char for char in alphabet if char not in key])  # ghép key và alphabet còn lại
    return [table[i:i+5] for i in range(0, 25, 5)]  # chia thành bảng 5x5

# Tìm vị trí của một ký tự trong bảng
def find_position(c, table):
    for i, row in enumerate(table):
        if c in row:
            return i, row.index(c)
    return None, None

# Mã hóa các cặp ký tự
def encrypt_pair(c1, c2, table):
    row1, col1 = find_position(c1, table)
    row2, col2 = find_position(c2, table)

    if row1 == row2:
        return table[row1][(col1 + 1) % 5] + table[row2][(col2 + 1) % 5]
    elif col1 == col2:
        return table[(row1 + 1) % 5][col1] + table[(row2 + 1) % 5][col2]
    else:
        return table[row1][col2] + table[row2][col1]

# Xử lý đầu vào
def playfair_cipher(text, key):
    text = text.lower().replace('j', 'i').replace(' ', '')  # làm sạch văn bản
    table = create_playfair_table(key)

    # Chia văn bản thành các cặp ký tự
    if len(text) % 2 != 0:
        text += 'x'  # nếu số lượng ký tự lẻ, thêm 'x'
    
    cipher_text = ''
    for i in range(0, len(text), 2):
        c1, c2 = text[i], text[i+1]
        cipher_text += encrypt_pair(c1, c2, table)
    
    return cipher_text

# Nhập đầu vào từ người dùng
key = input("Nhập key (khóa mã hóa): ").strip()
plaintext = input("Nhập văn bản cần mã hóa: ").strip()

cipher = playfair_cipher(plaintext, key)
print("Văn bản mã hóa:", cipher)
