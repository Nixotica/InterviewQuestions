 


def NumDaysBetween(year1, month1, day1, year2, month2, day2):
    min_month = 1
    max_month = 12
    total_days = 0
    
    # Get all the days for each month-year pair including the days outside the first and last month
    for year in range(year1, year2 + 1):
        for month in range(min_month, max_month + 1):
            if year == year1 and month < month1:
                continue
            if year == year2 and month > month2:
                continue
            total_days += DaysInMonth(month, year)
            print(f"adding {total_days} days at {year} {month}")

    # Subtract off the number of days in the first month before the date
    total_days -= day1
    print(f"subtracting {day1} days")

    # Subtract off the number of days in the last month after the date
    total_days -= DaysInMonth(month2, year2) - day2
    print(f"subtracting {DaysInMonth(month2, year2) - day2} days")

    # Return the number of days between the two dates
    return total_days


def DaysInMonth(month, year):
    return 30


# print(NumDaysBetween(2022, 11, 12, 2023, 9, 28))
# print(NumDaysBetween(2022, 11, 12, 2022, 11, 12))
# print(NumDaysBetween(2022, 11, 12, 2022, 11, 13))
# print(NumDaysBetween(1970, 1, 1, 2023, 11, 25))
print(NumDaysBetween(2022, 11, 12, 2022, 12, 6))