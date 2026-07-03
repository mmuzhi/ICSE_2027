#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream> // not strictly needed but included for completeness

struct Job {
    std::string job_title;
    std::string company;
    std::vector<std::string> requirements;
};

struct Resume {
    std::string name;
    std::vector<std::string> skills;
    std::string experience;
};

class JobMarketplace {
public:
    std::vector<Job> job_listings;
    std::vector<Resume> resumes;

    void post_job(const std::string& job_title, const std::string& company, const std::vector<std::string>& requirements) {
        Job job{job_title, company, requirements};
        job_listings.push_back(job);
    }

    void remove_job(const Job& job) {
        auto it = std::find_if(job_listings.begin(), job_listings.end(),
            [&](const Job& j) {
                return j.job_title == job.job_title &&
                       j.company == job.company &&
                       j.requirements == job.requirements;
            });
        if (it != job_listings.end()) {
            job_listings.erase(it);
        }
    }

    void submit_resume(const std::string& name, const std::vector<std::string>& skills, const std::string& experience) {
        Resume resume{name, skills, experience};
        resumes.push_back(resume);
    }

    void withdraw_resume(const Resume& resume) {
        auto it = std::find_if(resumes.begin(), resumes.end(),
            [&](const Resume& r) {
                return r.name == resume.name &&
                       r.skills == resume.skills &&
                       r.experience == resume.experience;
            });
        if (it != resumes.end()) {
            resumes.erase(it);
        }
    }

    std::vector<Job> search_jobs(const std::string& criteria) const {
        std::vector<Job> matching_jobs;
        std::string criteria_lower = to_lower(criteria);
        for (const auto& job : job_listings) {
            std::string title_lower = to_lower(job.job_title);
            // sub-string match in job title
            if (title_lower.find(criteria_lower) != std::string::npos) {
                matching_jobs.push_back(job);
                continue;
            }
            // exact match in any requirement (case-insensitive)
            bool found_in_requirements = false;
            for (const auto& req : job.requirements) {
                if (to_lower(req) == criteria_lower) {
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

    std::vector<Resume> get_job_applicants(const Job& job) const {
        std::vector<Resume> applicants;
        for (const auto& resume : resumes) {
            if (matches_requirements(resume, job.requirements)) {
                applicants.push_back(resume);
            }
        }
        return applicants;
    }

    static bool matches_requirements(const Resume& resume, const std::vector<std::string>& requirements) {
        for (const auto& skill : resume.skills) {
            if (std::find(requirements.begin(), requirements.end(), skill) == requirements.end()) {
                return false;
            }
        }
        return true;
    }

private:
    static std::string to_lower(const std::string& str) {
        std::string lower_str = str;
        std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(),
            [](unsigned char c) { return std::tolower(c); });
        return lower_str;
    }
};