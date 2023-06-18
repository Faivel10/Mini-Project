import csv
import os


for file in os.listdir("./output"):
    if os.path.isfile(os.path.join("./output/", file)):
        print(file)
        file_path  = "./output/" + str(file)
        with open(file_path, 'r') as file:
            lines = file.readlines()        
            # Create a CSV file for writing
            file_new_loc = "./output-csv/" + file.name
            with open(str(file_new_loc), 'w', newline='') as csvfile:
                writer = csv.writer(csvfile)
                for line in lines:
                    x, y = line.strip().split(' ')
                    writer.writerow([x, y])