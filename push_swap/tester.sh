#!/bin/bash

# Default values
RUNS=1
NUMBERS=100
THRESHOLD=500
BELOW_THRESHOLD_COUNT=0
TOTAL_MOVES=0
PRINT_MOVES=0

# Parse flags
while getopts "r:n:t:p" opt; do
  case $opt in
    r) RUNS=$OPTARG ;;        # Number of runs
    n) NUMBERS=$OPTARG ;;     # Number of random numbers
    t) THRESHOLD=$OPTARG ;;   # Threshold for move count
    p) PRINT_MOVES=1 ;;       # Print the move sequence
    *)
      echo "Usage: $0 [-r runs] [-n numbers] [-t threshold] [-p]"
      exit 1
      ;;
  esac
done

# Ensure valid input
if [[ $RUNS -lt 1 || $NUMBERS -lt 1 || $THRESHOLD -lt 1 ]]; then
  echo "Error: All values for -r, -n, and -t must be positive integers."
  exit 1
fi

# Run the tests
for (( i=1; i<=RUNS; i++ )); do
  INPUT=$(seq -1000 1000 | shuf -n $NUMBERS | tr '\n' ' ')
  OUTPUT=$(./push_swap $INPUT)
  MOVE_COUNT=$(echo "$OUTPUT" | wc -l)
  TOTAL_MOVES=$((TOTAL_MOVES + MOVE_COUNT))

  # echo "Run $i:"
  # echo "Input: $INPUT"
  # echo "Number of moves: $MOVE_COUNT"

  if (( PRINT_MOVES == 1 )); then
    echo "Move sequence:"
    echo "$OUTPUT"
  fi

  if (( MOVE_COUNT < THRESHOLD )); then
    BELOW_THRESHOLD_COUNT=$((BELOW_THRESHOLD_COUNT + 1))
  fi
done

# Calculate average
if (( RUNS > 0 )); then
  AVERAGE_MOVES=$(echo "scale=2; $TOTAL_MOVES / $RUNS" | bc)
else
  AVERAGE_MOVES=0
fi

# Display summary
echo "Summary:"
echo "Total runs: $RUNS"
echo "Average number of moves: $AVERAGE_MOVES"
echo "Number of runs with moves below $THRESHOLD: $BELOW_THRESHOLD_COUNT"
