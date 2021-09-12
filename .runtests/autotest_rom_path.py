
import json
import sys


def check_rom_include_line(abs_file_path: str, abs_rom_path: str) -> bool:
    """
    Determines if the rom in the autotest.json file is <abs_rom_path>.

    Pre:  <abs_file_path> must be an absolute system path to an existing
          autotest.json file.
          <abs_rom_path> must be an absolute system path to an existing ROM
          file.
    Post: True returned if ROM path in autotest.json file is the same as
          <abs_rom_path>.
          False returned otherwise.
    """

    same_rom_paths: bool = False

    with open(abs_file_path, "r") as f: 
        autotest_dict = json.load(f)
        if autotest_dict["rom"] == abs_rom_path:
            same_rom_paths = True

    return same_rom_paths


def write_rom_include_line(abs_file_path: str, abs_rom_path: str) -> None:
    """
    Writes <abs_rom_path> to the rom key in the autotest.json file.

    Pre:  <abs_file_path> must be an absolute system path to an existing
          autotest.json file.
          <abs_rom_path> must be an absolute system path to an existing ROM
          file.
    Post: True returned if ROM path in autotest.json file is the same as
          <abs_rom_path>.
          False returned otherwise.
    """

    with open(abs_file_path, "r") as f:
        autotest_dict = json.load(f)
        autotest_dict["rom"] = abs_rom_path

    with open(abs_file_path, "w") as f:
        json.dump(autotest_dict, f, indent=2)

    return


if __name__ == "__main__":
    if not check_rom_include_line(sys.argv[1], sys.argv[2]):
        write_rom_include_line(sys.argv[1], sys.argv[2])