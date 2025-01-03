import csv
import sys


def main():

    # TODO: Check for command-line usage -- done
    if len(sys.argv) != 3:
        sys.exit(1)

    # TODO: Read database file into a variable -- done
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        # print(reader.fieldnames)
        str_list = reader.fieldnames

    # TODO: Read DNA sequence file into a variable -- done
    sequenceDNA = open(sys.argv[2])
    tmp = sequenceDNA.read()
    str_list = str_list[1:len(str_list)+1]
    # print(str_list)

    # TODO: Find longest match of each STR in DNA sequence -- done
    profile = []
    for str in str_list:
        longest_run = longest_match(tmp, str)
        profile.append(longest_run)

    # TODO: Check database for matching profiles -- done
    rows = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            rows.append(row)
    # print(rows)

    for i in rows:
        match = True
        for j, STR in enumerate(str_list):
            if int(i[STR]) != profile[j]:
                match = False
                break
        if match:
            print(i['name'])
            break

    else:
        print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
