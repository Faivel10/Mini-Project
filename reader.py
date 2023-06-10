import xlrd

workbook = xlrd.open_workbook("data.xlsx")

#for now only first sheet testing
worksheet = workbook.sheet_by_index(0)
pairs = []
counter = 0
for i in range(1, 1001):
    pairs.append((worksheet.cell_value(i, 0), worksheet.cell_value(i, 1)))

with open("parsed", "w") as file:
    for pair in pairs:
        pair_str = [str(element) for element in pair]
        # Join the pair elements with a comma separator
        line = " ".join(pair_str)
        # Write the line to the file
        file.write(line + "\n")
