with open('hello', 'rb') as f:
    content = f.read()

original_string = b"Hello, World!"
# Note: "Hacked, World!" is 14 characters, which is longer than the 13-character original. 
# To prevent binary corruption, we use exactly 13 characters: "Hacked World!"
new_string = b"Hacked World!"

if original_string in content:
    content = content.replace(original_string, new_string)
    with open('hello', 'wb') as f:
        f.write(content)
    print("Successfully patched binary!")
else:
    print("Could not find the target string in the binary.")
