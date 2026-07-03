#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <cctype>

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

class JobMarketplace {
private:
    std::vector<Job> job_listings;
    std::vector<Resume> resumes;

    static bool matches_requirements(const Resume& resume, const std::vector<std::string>& requirements) {
        for (const std::string& skill : resume.skills) {
            if (std::find(requirements.begin(), requirements.end(), skill) == requirements.end()) {
                return false;
            }
        }
        return true;
    }

    static std::string toLower(const std::string& str) {
        std::string lowerStr = str;
        std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), 
                       [](unsigned char c) { return std::tolower(c); });
        return lowerStr;
    }

public:
    JobMarketplace() : job_listings(), resumes() {}

    void post_job(const std::string& job_title, const std::string& company, const std::vector<std::string>& requirements) {
        Job newJob;
        newJob.job_title = job_title;
        newJob.company = company;
        newJob.requirements = requirements;
        job_listings.push_back(newJob);
    }

    void remove_job(const Job& job) {
        auto it = std::find(job_listings.begin(), job_listings.end(), job);
        if (it == job_listings.end()) {
            throw std::invalid_argument("Job not found");
        }
        job_listings.erase(it);
    }

    void submit_resume(const std::string& name, const std::vector<std::string>& skills, const std::string& experience) {
        Resume newResume;
        newResume.name = name;
        newResume.skills = skills;
        newResume.experience = experience;
        resumes.push_back(newResume);
    }

    void withdraw_resume(const Resume& resume) {
        auto it = std::find(resumes.begin(), resumes.end(), resume);
        if (it == resumes.end()) {
            throw std::invalid_argument("Resume not found");
        }
        resumes.erase(it);
    }

    std::vector<Job> search_jobs(const std::string& criteria) {
        std::vector<Job> matching_jobs;
        std::string criteria_lower = toLower(criteria);

        for (const Job& job : job_listings) {
            std::string title_lower = toLower(job.job_title);
            bool found_in_title = (title_lower.find(criteria_lower) != std::string::npos);

            bool found_in_requirements = false;
            for (const std::string& req : job.requirements) {
                std::string req_lower = toLower(req);
                if (req_lower == criteria_lower) {
                    found_in_requirements = true;
                    break;
                }
            }

            if (found_in_title || found_in_requirements) {
                matching_jobs.push_back(job);
            }
        }

        return matching_jobs;
    }

    std::vector<Resume> get_job_applicants(const Job& job) {
        std::vector<Resume> applicants;
        for (const Resume& resume : resumes) {
            if (matches_requirements(resume, job.requirements)) {
                applicants.push_back(resume);
            }
        }
        return applicants;
    }
};