# Laboratory Work 10 - Final Report
**Topic:** Software Protection Using Obfuscation Algorithms
**Student:** [Gevorg Ghazaryan]

## Objective
To understand and demonstrate how code obfuscation techniques can protect software by making it difficult for humans or reverse engineering tools to analyze, without altering its original functionality.

## Step 1: String Encoding (Data Obfuscation)
We examined how sensitive data, such as strings or passwords, can be hidden within the code using XOR encryption.

**Python Implementation:**
```python
def encode(text, key):
    return [ord(c) ^ key for c in text]

def decode(data, key):
    return ''.join(chr(c ^ key) for c in data)
```
When running `encode("Secret", 12)` the text is converted into an array of integers (e.g., `[79, 97, 107, 126, 97, 124]`). This ensures the plain text string `"Secret"` does not appear directly in the compiled binary, effectively hiding it from basic static analysis.

## Step 2: Dead Code & Control Flow Obfuscation
We explored how to complicate the program's execution flow.

**Python Implementation (`control_flow.py`):**
```python
def hidden_multiply(a, b):
    state = 0
    result = 0

    while True:
        if state == 0:
            result = a * b
            state = 1
        elif state == 1:
            break

    return result
```
Instead of a simple multiplication, a state machine is used with a `while (True)` loop. In the C++ equivalent (`controlflow.cpp`), we also observed **dead code injection** where a `for` loop executes meaningless calculations (`temp = i * 999`) that are never used. This confuses decompilers (like Ghidra/IDA) by cluttering the Control Flow Graph.

## Step 3: Advanced Obfuscation (C++)
In `AdvancedObfuscation.cpp`, more complex techniques were demonstrated to further obscure logic:
- **Macro Substitution:** Replacing a simple addition `a+b` with the bitwise equivalent `((a ^ b) + 2*(a & b))` to obscure simple math.
- **Template Obfuscation:** Offloading calculations to the compiler (compile-time execution), meaning the runtime computation logic is completely absent from the final binary.
- **Inline Assembly:** Using low-level CPU instructions (`__asm__` block) which heavily disrupts static analysis tools.

## Conclusion
Obfuscation techniques such as XOR string encoding, dead code injection, and control flow flattening significantly increase the complexity of reverse engineering and protecting against patches/cracks. While these methods secure intellectual property and hide sensitive data (like API keys), they introduce a trade-off by making the source code harder to maintain and potentially introducing slight runtime performance overheads.

---

## Appendix: Complete Source Code

### 1. `xor.cpp`
```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Encode function
vector<int> xor_encode(const string& text, int key) {
    vector<int> encoded;
    for (char c : text) {
        encoded.push_back(c ^ key);
    }
    return encoded;
}

// Decode function
string xor_decode(const vector<int>& data, int key) {
    string decoded;
    for (int val : data) {
        decoded.push_back(char(val ^ key));
    }
    return decoded;
}

int main() {
    string original = "Hello World";
    int key = 23;

    vector<int> encoded = xor_encode(original, key);

    cout << "Encoded: ";
    for (int val : encoded) {
        cout << val << " ";
    }
    cout << endl;

    string decoded = xor_decode(encoded, key);
    cout << "Decoded: " << decoded << endl;

    return 0;
}
```

### 2. `controlflow.cpp`
```cpp
#include <iostream>

using namespace std;

int obfuscated_sum(int a, int b) {
    int result = 0;

    // Dead code (չօգտագործվող)
    for (int i = 0; i < 5; i++) {
        int temp = i * 999; // useless
    }

    // Control Flow Obfuscation
    int state = 0;

    while (true) {
        if (state == 0) {
            result = a + b;
            state = 1;
        }
        else if (state == 1) {
            break;
        }
    }

    return result;
}

int main() {
    cout << "Result: " << obfuscated_sum(5, 7) << endl;
    return 0;
}
```

### 3. `AdvancedObfuscation.cpp`
```cpp
// Macro-based Obfuscation

// a+b-ը փոխարինվում է բիթային մաթեմատիկայով
#define ADD(a,b) ((a ^ b) + 2*(a & b))



// Template Obfuscation
//Հաշվարկը կատարվում է compile-time-ում
// Reverse engineering-ը բարդանում է

template<int A, int B>
struct Add {
    static const int value = A + B;
};



// Inline ASM (Low-level Obfuscation)

int add(int a, int b) {
    int result;
    __asm__ (
        "addl %%ebx, %%eax;"
        : "=a"(result)
        : "a"(a), "b"(b)
    );
    return result;
}




int main() {
    int x = 5, y = 3;
    int result1 = ADD(x,y);

	int result2 = Add<5, 3>::value;

	int result3 = add(5, 3);


}
```

### 4. `obfuscation.py`
```python
def xor_encode(text, key):
    return [ord(c) ^ key for c in text]

def xor_decode(data, key):
    return ''.join(chr(c ^ key) for c in data)



def obfuscated_sum(a, b):
    result = 0

    # Dead code
    for i in range(5):
        temp = i * 999  # useless

    # Control flow obfuscation
    x = 0
    while True:
        if x == 0:
            result = a + b
            x = 1
        elif x == 1:
            break

    return result



original = "Hello World"
key = 23

encoded = xor_encode(original, key)
print("Encoded:", encoded)

decoded = xor_decode(encoded, key)
print("Decoded:", decoded)


print(obfuscated_sum(5, 7))
```

### 5. `main.py`
```python
from xor_obfuscation import encode, decode
from control_flow import hidden_multiply

text = "Secret"
key = 12

enc = encode(text, key)
print("Encoded:", enc)

dec = decode(enc, key)
print("Decoded:", dec)

print("Multiply:", hidden_multiply(3, 4))
```
