import csv
import os


for file in os.listdir("./non-csv-output"):
    if os.path.isfile(os.path.join("./non-csv-output/", file)):
        print(file)
        file_path  = "./non-csv-output/" + str(file)
        with open(file_path, 'r') as file:
            lines = file.readlines()
            # Create a CSV file for writing
            file_new_loc = "./output/" + file.name.split("/")[2] + ".csv"
            with open(str(file_new_loc), 'w', newline='') as csvfile:
                writer = csv.writer(csvfile)
                for line in lines:
                    x, y = line.strip().split(' ')
                    writer.writerow([x, y])
                