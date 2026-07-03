#include <vector>
#include <string>
#include <algorithm>
#include <cstddef> // for size_t

class JobMarketplace {
private:
    std::vector<JobListing> jobListings;
    std::vector<Resume> resumes;

public:
    void postJob(const std::string& title, const std::string& company, const std::vector<std::string>& requirements) {
        jobListings.emplace_back(title, company, requirements);
    }

    void removeJob(const JobListing& job) {
        auto it = std::find(jobListings.begin(), jobListings.end(), job);
        if (it != jobListings.end()) {
            jobListings.erase(it);
        }
    }

    void submitResume(const std::string& name, const std::vector<std::string>& skills, const std::string& experience) {
        resumes.emplace_back(name, skills, experience);
    }

    void withdrawResume(const Resume& resume) {
        auto it = std::find(resumes.begin(), resumes.end(), resume);
        if (it != resumes.end()) {
            resumes.erase(it);
        }
    }

    std::vector<JobListing> searchJobs(const std::string& skill) const {
        std::vector<JobListing> result;
        for (const auto& job : jobListings) {
            if (std::find(job.requirements.begin(), job.requirements.end(), skill) != job.requirements.end()) {
                result.push_back(job);
            }
        }
        return result;
    }

    std::vector<Resume> getJobApplicants(const JobListing& job) const {
        std::vector<Resume> result;
        for (const auto& resume : resumes) {
            if (resume.matchesRequirements(job.requirements)) {
                result.push_back(resume);
            }
        }
        return result;
    }

    // Accessor methods
    const std::vector<JobListing>& getJobListings() const { return jobListings; }
    const std::vector<Resume>& getResumes() const { return resumes; }

    class JobListing {
    private:
        std::string title;
        std::string company;
        std::vector<std::string> requirements;

    public:
        JobListing(const std::string& title, const std::string& company, const std::vector<std::string>& requirements)
            : title(title), company(company), requirements(requirements) {}

        const std::string& getTitle() const { return title; }
        const std::string& getCompany() const { return company; }
        const std::vector<std::string>& getRequirements() const { return requirements; }

        bool operator==(const JobListing& other) const {
            return title == other.title && 
                   company == other.company && 
                   requirements == other.requirements;
        }
    };

    class Resume {
    private:
        std::string name;
        std::vector<std::string> skills;
        std::string experience;

    public:
        Resume(const std::string& name, const std::vector<std::string>& skills, const std::string& experience)
            : name(name), skills(skills), experience(experience) {}

        const std::string& getName() const { return name; }
        const std::vector<std::string>& getSkills() const { return skills; }
        const std::string& getExperience() const { return experience; }

        bool matchesRequirements(const std::vector<std::string>& requirements) const {
            if (skills.size() != requirements.size()) return false;
            for (const auto& req : requirements) {
                if (std::find(skills.begin(), skills.end(), req) == skills.end()) {
                    return false;
                }
            }
            return true;
        }

        bool operator==(const Resume& other) const {
            return name == other.name && 
                   skills == other.skills && 
                   experience == other.experience;
        }
    };
};