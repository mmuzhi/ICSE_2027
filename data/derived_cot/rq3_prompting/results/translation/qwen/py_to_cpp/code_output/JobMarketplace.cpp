#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

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
    JobMarketplace() : job_listings(), resumes() {}

    void post_job(const std::string& job_title, const std::string& company, const std::vector<std::string>& requirements) {
        Job job = {job_title, company, requirements};
        job_listings.push_back(job);
    }

    void remove_job(const Job& job) {
        auto it = std::find_if(job_listings.begin(), job_listings.end(), [&job](const Job& j) {
            return j.job_title == job.job_title && j.company == job.company && j.requirements == job.requirements;
        });
        if (it != job_listings.end()) {
            job_listings.erase(it);
        }
    }

    void submit_resume(const std::string& name, const std::vector<std::string>& skills, const std::string& experience) {
        Resume resume = {name, skills, experience};
        resumes.push_back(resume);
    }

    void withdraw_resume(const Resume& resume) {
        auto it = std::find_if(resumes.begin(), resumes.end(), [&resume](const Resume& r) {
            return r.name == resume.name && r.skills == resume.skills && r.experience == resume.experience;
        });
        if (it != resumes.end()) {
            resumes.erase(it);
        }
    }

    std::vector<Job> search_jobs(const std::string& criteria) {
        std::vector<Job> matching_jobs;
        for (const auto& job : job_listings) {
            bool found_in_title = false;
            if (!criteria.empty()) {
                auto lower_criteria = to_lower(criteria);
                auto lower_title = to_lower(job.job_title);
                if (lower_title.find(lower_criteria) != std::string::npos) {
                    found_in_title = true;
                }
            }
            if (!found_in_title) {
                for (const auto& req : job.requirements) {
                    if (req.find(criteria) != std::string::npos) {
                        found_in_title = true;
                        break;
                    }
                }
            }
            if (found_in_title) {
                matching_jobs.push_back(job);
            }
        }
        return matching_jobs;
    }

    std::vector<Resume> get_job_applicants(const Job& job) {
        std::vector<Resume> applicants;
        for (const auto& resume : resumes) {
            bool matches = true;
            for (const auto& skill : resume.skills) {
                bool found = false;
                for (const auto& req : job.requirements) {
                    if (skill == req) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    matches = false;
                    break;
                }
            }
            if (matches) {
                applicants.push_back(resume);
            }
        }
        return applicants;
    }

private:
    std::vector<Job> job_listings;
    std::vector<Resume> resumes;

    static std::string to_lower(const std::string& s) {
        std::string result;
        for (char c : s) {
            result.push_back(std::tolower(static_cast<unsigned char>(c)));
        }
        return result;
    }
};