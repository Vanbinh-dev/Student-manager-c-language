#include "../include/student.h"

char *getGenderName(int value) {
    if (value == MALE)
        return "MALE";
    return "FEMALE";
}

char *getStudyStatusName(int value) {
    switch (value) {
        case ENROLLED:    
            return "Enrolled";
        case ON_LEAVE:    
            return "On Leave";
        case WITHDRAWN:  
            return "Withdrawn";
        case GRADUATED:   
            return "Graduated";
        case SUSPENDED:   
            return "Suspended";
        case TRANSFERRED: 
            return "Transferred";
    }

    return "Enrolled";
}

char *getMajorName(int value) {
    switch (value) {
    case AI:
        return "Artificial Intelligence";
    case SE:
        return "Software Engineering";
    case IC:
        return "Integrated Circuit";
    case NET:
        return "Network Engineering";
    case DA:
        return "Data Analytics";
    case DS:
        return "Data Science";
    case TE:
        return "Tester";
    }

    return "Software Engineering";
}

char *newId() {
    return "0000 0000";
}