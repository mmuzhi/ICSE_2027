#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cctype>

class JobMarketplace {
public:
    struct Job {
        std::string job_title;
        std::string company;
        std::vector<std::string> requirements;

        bool operator==(const Job& other) const {
            return job_title == other.job_title && 
                   company == other.company && 
                   requirements == other.requirements;
        }
    };

    struct Resume {
        std::string name;
        std::vector<std::string> skills;
        std::string experience;

        bool operator==(const Resume& other) const {
            return name == other.name && 
                   skills == other.skills && 
                   experience == other.experience;
        }
    };

    std::vector<Job> job_listings;
    std::vector<Resume> resumes;

    JobMarketplace() = default;

    void post_job(const std::string& job_title, const std::string& company, const std::vector<std::string>& requirements) {
        job_listings.push_back({job_title, company, requirements});
    }

    void remove_job(const Job& job) {
        auto it = std::find(job_listings.begin(), job_listings.end(), job);
        if (it != job_listings.end()) {
            job_listings.erase(it);
        } else {
            throw std::runtime_error("Job not found");
        }
    }

    void submit_resume(const std::string& name, const std::vector<std::string>& skills, const std::string& experience) {
        resumes.push_back({name, skills, experience});
    }

    void withdraw_resume(const Resume& resume) {
        auto it = std::find(resumes.begin(), resumes.end(), resume);
        if (it != resumes.end()) {
            resumes.erase(it);
        } else {
            throw std::runtime_error("Resume not found");
        }
    }

    std::vector<Job> search_jobs(const std::string& criteria) const {
        std::vector<Job> matching_jobs;
        std::string lower_criteria = to_lower(criteria);
        
        for (const auto& job_listing : job_listings) {
            // criteria in job_title is a substring match
            bool match = to_lower(job_listing.job_title).find(lower_criteria) != std::string::npos;
            
            if (!match) {
                // criteria in requirements is an exact match against the list elements
                for (const auto& r : job_listing.requirements) {
                    if (to_lower(r) == lower_criteria) {
                        match = true;
                        break;
                    }
                }
            }
            
            if (match) {
                matching_jobs.push_back(job_listing);
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
    static std::string to_lower(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return std::tolower(c); });
        return str;
    }
};