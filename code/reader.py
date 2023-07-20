import xlrd

workbook = xlrd.open_workbook("data.xlsx")
sheet_names = workbook.sheet_names()
number_of_sheets = len(sheet_names)
print("there are: ", number_of_sheets, " sheets to calcualte")

counter = 1
for name in sheet_names:
    print("parsing values from sheet named: " + name)
    worksheet = workbook.sheet_by_name(name)
    pairs = []
    non_emptycells=[i for i,x in enumerate(worksheet.col(0)) if x.ctype != 0]
    print("There are : ", len(non_emptycells) -1, "points in this sheet")

    for i in range(1, len(non_emptycells)):#remove titles
        pairs.append((worksheet.cell_value(i, 0), worksheet.cell_value(i, 1)))

    #export for the main program to read.
    file_path = "parsed/parsed-" + name
    with open(file_path, "w") as file:
        for pair in pairs:
            pair_str = [str(element) for element in pair]
            # Join the pair elements with a comma separator
            line = " ".join(pair_str)
            # Write the line to the file
            file.write(line + "\n")

    counter = counter + 1
    