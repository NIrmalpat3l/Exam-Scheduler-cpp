#include <bits/stdc++.h>
using namespace std;

struct Exam
{
    int id;
    string name;
    int numStudents;
    vector<int> students;
};

struct Room
{
    int id;
    int capacity;
};

struct TimeSlot
{
    int id;
    string date;
    string slot;
};

struct Assignment
{
    int timeslot;
    int room;
};

bool haveConflict(const Exam &e1, const Exam &e2)
{
    unordered_set<int> students_e1(e1.students.begin(), e1.students.end());
    for (auto student : e2.students)
    {
        if (students_e1.find(student) != students_e1.end())
            return true;
    }
    return false;
}
// O(n)

vector<vector<bool>> buildConflictMatrix(const vector<Exam> &exams)
{
    int n = exams.size();
    vector<vector<bool>> conflict(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (haveConflict(exams[i], exams[j]))
            {
                conflict[i][j] = conflict[j][i] = true;
            }
        }
    }
    return conflict;
}
// O(e^2 * s) ~ O(s)
// e = no of exam
// s = avg no of students

int selectUnassignedExam(const vector<Assignment> &assignments, const vector<Exam> &exams,
                         const vector<vector<bool>> &conflict,
                         const vector<Room> &rooms,
                         const vector<TimeSlot> &timeslots,
                         const vector<vector<pair<int, int>>> &domains)
{
    int n = exams.size();
    int selected = -1;
    int minRemaining = INT32_MAX;
    for (int i = 0; i < n; i++)
    {
        if (assignments[i].timeslot == -1)
        {
            int remaining = domains[i].size();
            if (remaining < minRemaining)
            {
                minRemaining = remaining;
                selected = i;
            }
        }
    }
    return selected;
}
// O(e)
// e = no of exam

vector<pair<int, int>> orderDomainValues(int exam, const vector<Exam> &exams,
                                         const vector<Assignment> &assignments,
                                         const vector<vector<bool>> &conflict,
                                         const vector<Room> &rooms,
                                         const vector<TimeSlot> &timeslots,
                                         const vector<vector<pair<int, int>>> &domains)
{
    return domains[exam];
}
// O(d)
// d = size of domain
// domain = possible assign order for each exam in term of rooms and students
bool isValid(int exam, pair<int, int> assign, const vector<Assignment> &assignments,
             const vector<Exam> &exams, const vector<Room> &rooms,
             const vector<TimeSlot> &timeslots,
             const vector<vector<bool>> &conflict)
{
    int ts = assign.first;
    int rm = assign.second;
    if (rooms[rm].capacity < exams[exam].numStudents)
        return false;
    for (int i = 0; i < exams.size(); i++)
    {
        if (assignments[i].timeslot == ts)
        {
            if (assignments[i].room == rm)
                return false;
            if (conflict[exam][i])
                return false;
        }
    }
    return true;
}
// O(e)
// e = no of exam

bool backtrack(vector<Assignment> &assignments, const vector<Exam> &exams,
               const vector<Room> &rooms, const vector<TimeSlot> &timeslots,
               const vector<vector<bool>> &conflict,
               vector<vector<pair<int, int>>> &domains)
{
    bool complete = true;
    for (auto &a : assignments)
    {
        if (a.timeslot == -1)
        {
            complete = false;
            break;
        }
    }
    if (complete)
        return true;

    int exam = selectUnassignedExam(assignments, exams, conflict, rooms, timeslots, domains);
    if (exam == -1)
        return false;

    vector<pair<int, int>> ordered = orderDomainValues(exam, exams, assignments, conflict, rooms, timeslots, domains);

    for (auto &assign : ordered)
    {
        if (isValid(exam, assign, assignments, exams, rooms, timeslots, conflict))
        {
            assignments[exam] = {assign.first, assign.second};

            vector<vector<pair<int, int>>> domains_backup = domains;

            for (int i = 0; i < exams.size(); i++)
            {
                if (conflict[exam][i] && assignments[i].timeslot == -1)
                {
                    vector<pair<int, int>> new_domain;
                    for (auto &a : domains[i])
                    {
                        if (a.first != assign.first || a.second != assign.second)
                        {
                            new_domain.push_back(a);
                        }
                    }
                    domains[i] = new_domain;
                    if (domains[i].empty())
                    {
                        assignments[exam] = {-1, -1};
                        domains = domains_backup;
                        goto next_assignment;
                    }
                }
            }

            if (backtrack(assignments, exams, rooms, timeslots, conflict, domains))
                return true;

            assignments[exam] = {-1, -1};
            domains = domains_backup;
        }
    next_assignment:;
    }
    return false;
}
// O(d^e)
// d = size of domain
// e = exam

int main()
{
    vector<Exam> exams = {
        {1, "Mathematics", 3, {101, 102, 103}},
        {2, "Physics", 2, {102, 104}},
        {3, "Chemistry", 2, {105, 106}},
        {4, "Biology", 1, {107}},
        {5, "English", 2, {108, 109}},
    };

    vector<Room> rooms = {
        {201, 2},
        {202, 3},
        {203, 1},
        {204, 4},
    };

    vector<TimeSlot> timeslots = {
        {1, "2024-12-10", "Morning"},
        {2, "2024-12-10", "Afternoon"},
        {3, "2024-12-11", "Morning"},
        {4, "2024-12-11", "Afternoon"},
        {5, "2024-12-12", "Morning"},
        {6, "2024-12-12", "Afternoon"},
    };

    vector<vector<bool>> conflict = buildConflictMatrix(exams);

    vector<Assignment> assignments(exams.size(), {-1, -1});

    vector<vector<pair<int, int>>> domains(exams.size());
    for (int i = 0; i < exams.size(); i++)
    {
        for (int t = 0; t < timeslots.size(); t++)
        {
            for (int r = 0; r < rooms.size(); r++)
            {
                if (rooms[r].capacity >= exams[i].numStudents)
                    domains[i].emplace_back(make_pair(timeslots[t].id, rooms[r].id));
            }
        }
    }

    bool success = backtrack(assignments, exams, rooms, timeslots, conflict, domains);

    if (success)
    {
        cout << "Scheduling Successful!\n";
        for (int i = 0; i < assignments.size(); i++)
        {
            cout << "Exam " << exams[i].id << " (" << exams[i].name << ") scheduled on "
                 << "\"" << timeslots[assignments[i].timeslot - 1].date << "\", "
                 << timeslots[assignments[i].timeslot - 1].slot
                 << " in Room " << rooms[assignments[i].room].id << "\n";
        }
    }
    else
    {
        cout << "No feasible schedule found.\n";
    }

    return 0;
}

// O(e^2 * s + d + e + d^e) ~ O(d^e)
// in worst case Backtrack will check all of the possible assignments