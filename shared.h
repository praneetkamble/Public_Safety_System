#ifndef SHARED_H
#define SHARED_H

#include <time.h>

#define CASE_DB "cases.db"

/* ---------- CASE TYPES ---------- */
typedef enum {
    MEDICAL = 1,
    POLICE,
    FIRE,
    UTILITY,
    DISASTER,
    COMPLAINT
} CaseType;

/* ---------- CASE STATUS ---------- */
typedef enum {
    REGISTERED = 1,
    DISPATCHED,
    IN_PROGRESS,
    RESOLVED,
    CLOSED
} CaseStatus;

/* ---------- CASE STRUCT ---------- */
typedef struct {
    int case_id;
    CaseType type;
    char location[50];
    int severity;          // MUST be 1–5
    CaseStatus status;
    time_t created_time;
} Case;

/* ---------- ENUM → STRING ---------- */
static inline const char* status_to_string(CaseStatus s) {
    switch (s) {
        case REGISTERED:  return "Registered";
        case DISPATCHED:  return "Dispatched";
        case IN_PROGRESS: return "In Progress";
        case RESOLVED:    return "Resolved";
        case CLOSED:      return "Closed";
        default:          return "Unknown";
    }
}

static inline const char* type_to_string(CaseType t) {
    switch (t) {
        case MEDICAL:   return "Medical";
        case POLICE:    return "Police";
        case FIRE:      return "Fire";
        case UTILITY:   return "Utility";
        case DISASTER:  return "Disaster";
        case COMPLAINT: return "Complaint";
        default:        return "Unknown";
    }
}

#endif
