#include <vector>
#include <string>
#include <algorithm>
#include <utility>

class JobListing {
public:
    JobListing(std::string title, std::string company, std::vector<std::string> requirements)
        : title(std::move(title)), company(std::move(company)), requirements(std::move(requirements)) {}

    std::string getTitle() const { return title; }
    std::string getCompany() const { return company; }
    std::vector<std::string> getRequirements() const { return requirements; }

    bool operator==(const JobListing& other) const {
        return title == other.title && company == other.company && requirements == other.requirements;
    }

private:
    std::string title;
    std::string company;
    std::vector<std::string> requirements;
};

class Resume {
public:
    Resume(std::string name, std::vector<std::string> skills, std::string experience)
        : name(std::move(name)), skills(std::move(skills)), experience(std::move(experience)) {}

    std::string getName() const { return name; }
    std::vector<std::string> getSkills() const { return skills; }
    std::string getExperience() const { return experience; }

    bool operator==(const Resume& other) const {
        return name == other.name && skills == other.skills && experience == other.experience;
    }

private:
    std::string name;
    std::vector<std::string> skills;
    std::string experience;
};

class JobMarketplace {
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
            const auto& reqs = job.getRequirements();
            if (std::find(reqs.begin(), reqs.end(), skill) != reqs.end()) {
                result.push_back(job);
            }
        }
        return result;
    }

    std::vector<Resume> getJobApplicants(const JobListing& job) const {
        std::vector<Resume> result;
        const auto& reqs = job.getRequirements();
        for (const auto& resume : resumes) {
            if (matchesRequirements(resume, reqs)) {
                result.push_back(resume);
            }
        }
        return result;
    }

    bool matchesRequirements(const Resume& resume, const std::vector<std::string>& requirements) const {
        const auto& skills = resume.getSkills();
        if (skills.size() != requirements.size()) {
            return false;
        }
        for (const auto& req : requirements) {
            if (std::find(skills.begin(), skills.end(), req) == skills.end()) {
                return false;
            }
        }
        return true;
    }

    std::vector<JobListing>& getJobListings() { return jobListings; }
    const std::vector<JobListing>& getJobListings() const { return jobListings; }

    std::vector<Resume>& getResumes() { return resumes; }
    const std::vector<Resume>& getResumes() const { return resumes; }

private:
    std::vector<JobListing> jobListings;
    std::vector<Resume> resumes;
};