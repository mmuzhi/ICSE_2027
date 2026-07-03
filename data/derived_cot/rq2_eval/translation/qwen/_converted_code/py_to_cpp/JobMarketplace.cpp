#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

struct JobListing {
    string job_title;
    string company;
    vector<string> requirements;
};

struct Resume {
    string name;
    vector<string> skills;
    string experience;
};

bool operator==(const JobListing& lhs, const JobListing& rhs) {
    if (lhs.job_title != rhs.job_title) return false;
    if (lhs.company != rhs.company) return false;
    if (lhs.requirements.size() != rhs.requirements.size()) return false;
    for (const auto& req : lhs.requirements) {
        bool found = false;
        for (const auto& r : rhs.requirements) {
            if (req == r) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

bool operator==(const Resume& lhs, const Resume& rhs) {
    if (lhs.name != rhs.name) return false;
    if (lhs.experience != rhs.experience) return false;
    if (lhs.skills.size() != rhs.skills.size()) return false;
    for (const auto& skill : lhs.skills) {
        bool found = false;
        for (const auto& s : rhs.skills) {
            if (skill == s) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

class JobMarketplace {
private:
    vector<JobListing> job_listings;
    vector<Resume> resumes;

    bool matches_requirements(const Resume& resume, const vector<string>& requirements) {
        for (const auto& skill : resume.skills) {
            bool found = false;
            for (const auto& req : requirements) {
                if (skill == req) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                return false;
            }
        }
        return true;
    }

public:
    JobMarketplace() {}

    void post_job(const string& job_title, const string& company, const vector<string>& requirements) {
        JobListing job = {job_title, company, requirements};
        job_listings.push_back(job);
    }

    void remove_job(const JobListing& job) {
        job_listings.erase(remove(job_listings.begin(), job_listings.end(), job, [](const JobListing& j) { return j == job; }), job_listings.end());
    }

    void submit_resume(const string& name, const vector<string>& skills, const string& experience) {
        Resume resume = {name, skills, experience};
        resumes.push_back(resume);
    }

    void withdraw_resume(const Resume& resume) {
        resumes.erase(remove(resumes.begin(), resumes.end(), resume, [](const Resume& r) { return r == resume; }), resumes.end());
    }

    vector<JobListing> search_jobs(const string& criteria) {
        if (criteria.empty()) {
            return job_listings;
        }

        vector<JobListing> matching_jobs;
        string criteria_lower = criteria;
        transform(criteria_lower.begin(), criteria_lower.end(), criteria_lower.begin(), [](unsigned char c) { return tolower(c); });

        for (const auto& job : job_listings) {
            string job_title_lower = job.job_title;
            transform(job_title_lower.begin(), job_title_lower.end(), job_title_lower.begin(), [](unsigned char c) { return tolower(c); });
            if (job_title_lower.find(criteria_lower) != string::npos) {
                matching_jobs.push_back(job);
                continue;
            }

            bool found_in_requirements = false;
            for (const auto& req : job.requirements) {
                string req_lower = req;
                transform(req_lower.begin(), req_lower.end(), req_lower.begin(), [](unsigned char c) { return tolower(c); });
                if (req_lower.find(criteria_lower) != string::npos) {
                    found_in_requirements = true;
                    break;
                }
            }

            if (found_in_requirements) {
                matching_jobs.push_back(job);
            }
        }
        return matching_jobs;
    }

    vector<Resume> get_job_applicants(const JobListing& job) {
        vector<Resume> applicants;
        for (const auto& resume : resumes) {
            if (matches_requirements(resume, job.requirements)) {
                applicants.push_back(resume);
            }
        }
        return applicants;
    }
};