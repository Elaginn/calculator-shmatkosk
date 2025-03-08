import subprocess

def test_integer_mode():
    result = subprocess.run(["./build/app.exe"], input="3 + 5 * 2\n", text=True, capture_output=True)
    output = result.stdout.strip().splitlines()[-1]
    assert output == "13", f"Expected 13, got {output}"

def test_float_mode():
    result = subprocess.run(["./build/app.exe", "--float"], input="5 / 2\n", text=True, capture_output=True)
    output = result.stdout.strip().splitlines()[-1]
    assert output.startswith("2.5"), f"Expected output starting with 2.5, got {output}"

if __name__ == "__main__":
    test_integer_mode()
    test_float_mode()
    print("All integration tests passed.")

