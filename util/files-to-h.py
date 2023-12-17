#!/usr/bin/env python3

import sys
import subprocess

def main():
	for filename in sys.argv[1:]:
		print(f'Processing {filename}', file=sys.stderr)
		headerContent = subprocess.check_output(["xxd", "-i", filename])
		print(headerContent.decode("utf-8"))

if __name__ == "__main__":
	main()
