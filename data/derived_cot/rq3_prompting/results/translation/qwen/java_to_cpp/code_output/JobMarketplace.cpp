#include <vector>
#include <string>
#include <algorithm>

class JobMarketplace {
private:
    std::vector<JobListing> jobListings;
    std::vector<Resume> resumes;

public:
    JobMarketplace();

    void postJob(const std::string& title, const std::string& company, const std::vector<std::string>& requirements);
    void removeJob(JobListing job);
    void submitResume(const std::string& name, const std::vector<std::string>& skills, const std::string& experience);
    void withdrawResume(Resume resume);
    std::vector<JobListing> searchJobs(const std::string& skill);
    std::vector<Resume> getJobApplicants(const JobListing& job);
    std::vector<JobListing>& getJobListings();
    std::vector<Resume>& getResumes();

    class JobListing {
    private:
        std::string title;
        std::string company;
        std::vector<std::string> requirements;

    public:
        JobListing(const std::string& title, const std::string& company, const std::vector<std::string>& requirements);
        std::string getTitle() const;
        std::string getCompany() const;
        const std::vector<std::string>& getRequirements() const;
        bool operator==(const JobListing& other) const;
    };

    class Resume {
    private:
        std::string name;
        std::vector<std::string> skills;
        std::string experience;

    public:
        Resume(const std::string& name, const std::vector<std::string>& skills, const std::string& experience);
        std::string getName() const;
        const std::vector<std::string>& getSkills() const;
        std::string getExperience() const;
        bool operator==(const Resume& other) const;
    };
};

JobMarketplace::JobMarketplace() : jobListings(), resumes() {}

JobMarketplace::JobListing::JobListing(const std::string& title, const std::string& company, const std::vector<std::string>& requirements)
    : title(title), company(company), requirements(requirements) {}

JobMarketplace::JobListing::operator==(const JobListing& other) const {
    return title == other.title && company == other.company && requirements == other.requirements;
}

JobMarketplace::Resume::Resume(const std::string& name, const std::vector<std::string>& skills, const std::string& experience)
    : name(name), skills(skills), experience(experience) {}

JobMarketplace::Resume::operator==(const Resume& other) const {
    return name == other.name && skills == other.skills && experience == other.experience;
}

void JobMarketplace::postJob(const std::string& title, const std::string& company, const std::vector<std::string>& requirements) {
    jobListings.push_back(JobListing(title, company, requirements));
}

void JobMarketplace::removeJob(JobListing job) {
    jobListings.erase(std::remove(jobListings.begin(), jobListings.end(), job), jobListings.end());
}

void JobMarketplace::submitResume(const std::string& name, const std::vector<std::string>& skills, const std::string& experience) {
    resumes.push_back(Resume(name, skills, experience));
}

void JobMarketplace::withdrawResume(Resume resume) {
    resumes.erase(std::remove(resumes.begin(), resumes.end(), resume), resumes.end());
}

std::vector<JobListing> JobMarketplace::searchJobs(const std::string& skill) {
    std::vector<JobListing> result;
    for (const auto& job : jobListings) {
        if (std::find(job.getRequirements().begin(), job.getRequirements().end(), skill) != job.getRequirements().end()) {
            result.push_back(job);
        }
    }
    return result;
}

std::vector<Resume> JobMarketplace::getJobApplicants(const JobListing& job) {
    std::vector<Resume> result;
    for (const auto& resume : resumes) {
        if (matchesRequirements(resume, job.getRequirements())) {
            result.push_back(resume);
        }
    }
    return result;
}

bool JobMarketplace::matchesRequirements(const Resume& resume, const std::vector<std::string>& requirements) {
    if (resume.getSkills().size() != requirements.size()) return false;
    for (const auto& req : requirements) {
        if (std::find(resume.getSkills().begin(), resume.getSkills().end(), req) == resume.getSkills().end()) {
            return false;
        }
    }
    return true;
}

std::vector<JobListing>& JobMarketplace::getJobListings() {
    return jobListings;
}

std::vector<Resume>& JobMarketplace::getResumes() {
    return resumes;
}