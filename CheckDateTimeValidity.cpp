#define INT(Name)                \
    struct Name {                \
        int val;                 \
        explicit Name(int valx)  \
            : val(valx) {}       \
        operator int() const {   \
            return val;          \
        }                        \
    };                           \


INT(Year);
INT(Month);
INT(Day);
INT(Hour);
INT(Minute);
INT(Second);


struct DateTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    DateTime(Year yearx, Month monthx, Day dayx, Hour hourx, Minute minutex, Second secondx)
        : year(yearx)
        , month(monthx)
        , day(dayx)
        , hour(hourx)
        , minute(minutex)
        , second(secondx) {

        if (year < 1) {
            throw domain_error("year is too small"s);
        }
        if (year > 9999) {
            throw domain_error("year is too big"s);
        }

        if (month < 1) {
            throw domain_error("month is too small"s);
        }
        if (month > 12) {
            throw domain_error("month is too big"s);
        }

        if (day < 1) {
            throw domain_error("day is too small"s);
        }

        if (hour < 0) {
            throw domain_error("hour is too small"s);
        }
        if (hour > 23) {
            throw domain_error("hour is too big"s);
        }

        if (minute < 0) {
            throw domain_error("minute is too small"s);
        }
        if (minute > 59) {
            throw domain_error("minute is too big"s);
        }

        if (second < 0) {
            throw domain_error("second is too small");
        }
        if (second > 59) {
            throw domain_error("second is too big"s);
        }

    }

};


void CheckDateTimeValidity(const DateTime& dt) {

    const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
    const array month_lengths = {31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (dt.day > month_lengths[dt.month - 1]) {
        throw domain_error("day is too big"s);
    }
}


int main() {
    DateTime date_time( Year(2025), Month(7), Day(27), Hour(10), Minute(5), Second(6) );
    CheckDateTimeValidity(date_time);

}
