import os

def change_file_suffix(root_directory):
    for root, _, files in os.walk(root_directory):
        for filename in files:
            if filename.endswith(".cc"):
                old_path = os.path.join(root, filename)
                new_filename = os.path.splitext(filename)[0] + ".c"
                new_path = os.path.join(root, new_filename)
                os.rename(old_path, new_path)
                print(f"Renamed: {old_path} -> {new_path}")

if __name__ == "__main__":
    root_folder = os.path.dirname(os.path.abspath(__file__))
    change_file_suffix(root_folder)
