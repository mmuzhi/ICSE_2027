#ifndef JOB_MARKETPLACE_H
#define JOB_MARKETPLACE_H

#include <string>
#include <vector>
#include <algorithm>

class JobListing {
private:
    std::string title;
    std::string company;
    std::vector<std::string> requirements;

public:
    JobListing(std::string title, std::string company, std::vector<std::string> requirements)
        : title(std::move(title)), company(std::move(company)), requirements(std::move(requirements)) {}

    const std::string& getTitle() const { return title; }
    const std::string& getCompany() const { return company; }
    const std::vector<std::string>& getRequirements() const { return requirements; }

    bool operator==(const JobListing& that) const {
        return title == that.title && company == that.company && requirements == that.requirements;
    }

    bool operator!=(const JobListing& that) const {
        return !(*this == that);
    }
};

class Resume {
private:
    std::string name;
    std::vector<std::string> skills;
    std::string experience;

public:
    Resume(std::string name, std::vector<std::string> skills, std::string experience)
        : name(std::move(name)), skills(std::move(skills)), experience(std::move(experience)) {}

    const std::string& getName() const { return name; }
    const std::vector<std::string>& getSkills() const { return skills; }
    const std::string& getExperience() const { return experience; }

    bool operator==(const Resume& other) const {
        return name == other.name && skills == other.skills && experience == other.experience;
    }

    bool operator!=(const Resume& other) const {
        return !(*this == other);
    }
};

class JobMarketplace {
private:
    std::vector<JobListing> jobListings;
    std::vector<Resume> resumes;

public:
    JobMarketplace() = default;

    void postJob(std::string title, std::string company, std::vector<std::string> requirements) {
        jobListings.emplace_back(std::move(title), std::move(company), std::move(requirements));
    }

    void removeJob(const JobListing& job) {
        auto it = std::find(jobListings.begin(), jobListings.end(), job);
        if (it != jobListings.end()) {
            jobListings.erase(it);
        }
    }

    void submitResume(std::string name, std::vector<std::string> skills, std::string experience) {
        resumes.emplace_back(std::move(name), std::move(skills), std::move(experience));
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
            const auto& reqs = job.getRequirements();
            if (std::find(reqs.begin(), reqs.end(), skill) != reqs.end()) {
                result.push_back(job);
            }
        }
        return result;
    }

    std::vector<Resume> getJobApplicants(const JobListing& job) const {
        std::vector<Resume> result;
        for (const auto& resume : resumes) {
            if (matchesRequirements(resume, job.getRequirements())) {
                result.push_back(resume);
            }
        }
        return result;
    }

    bool matchesRequirements(const Resume& resume, const std::vector<std::string>& requirements) const {
        const std::vector<std::string>& skills = resume.getSkills();
        if (skills.size() != requirements.size()) return false;
        for (const auto& req : requirements) {
            if (std::find(skills.begin(), skills.end(), req) == skills.end()) {
                return false;
            }
        }
        return true;
    }

    std::vector<JobListing> getJobListings() const {
        return jobListings;
    }

    std::vector<Resume> getResumes() const {
        return resumes;
    }
};

#endif