#!/bin/bash

mp4=""
bf=""
w=96
h=38
fps=1440

while [[ $# -gt 0 ]]; do
  case "$1" in
    --help)
      echo "Usage: $0 -i <input.mp4> -o <output.bf> [-w <width>] [-h <height>] [-f <fps>]"
      echo
      echo "Options:"
      echo "  -i, --input     Input MP4 file"
      echo "  -o, --output    Output BF file"
      echo "  -w, --width     Width of output (default: 96)"
      echo "  -h, --height    Height of output (default: 38)"
      echo "  -f, --fps       Frames per second (default: 1440)"
      exit 0
      ;;
    -i|--input)
      mp4="$2"
      shift 2
      ;;
    -o|--output)
      bf="$2"
      shift 2
      ;;
    -w|--width)
      w="$2"
      shift 2
      ;;
    -h|--height)
      h="$2"
      shift 2
      ;;
    -f|--fps)
      fps="$2"
      shift 2
      ;;
    *)
      echo "Unknown option: $1"
      echo "Try '$0 --help' for usage."
      exit 1
      ;;
  esac
done

# Check required arguments
if [[ -z "$mp4" || -z "$bf" ]]; then
  echo "Error: Missing required arguments."
  echo "Try '$0 --help' for usage."
  exit 1
fi

# Check if input file exists
if [[ ! -f "$mp4" ]]; then
  echo "Error: Input file '$mp4' not found."
  exit 1
fi

gcc bmp2bf.c -o bmp2bf
# Convert MP4 to BF
ffmpeg -i "$mp4" -vf "fps=${fps},scale=${w}:${h}" -vcodec bmp -f image2pipe - | \
  ./bmp2bf "$w" "$h" > "$bf"

if [[ $? -ne 0 ]]; then
  echo "Error: Conversion failed."
  exit 1
fi

echo "Successfully converted '$mp4' to '$bf' (${w}x${h}, ${fps}fps)."

