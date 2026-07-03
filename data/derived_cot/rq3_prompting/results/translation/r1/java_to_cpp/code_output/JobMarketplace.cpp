#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <stdexcept>

class JobMarketplace {
public:
    class JobListing {
    private:
        std::string title;
        std::string company;
        std::vector<std::string> requirements;

    public:
        JobListing(const std::string& title, const std::string& company,
                   const std::vector<std::string>& requirements)
            : title(title), company(company), requirements(requirements) {}

        const std::string& getTitle() const { return title; }
        const std::string& getCompany() const { return company; }
        const std::vector<std::string>& getRequirements() const { return requirements; }

        bool operator==(const JobListing& other) const {
            return title == other.title &&
                   company == other.company &&
                   requirements == other.requirements;
        }

        bool operator!=(const JobListing& other) const { return !(*this == other); }
    };

    class Resume {
    private:
        std::string name;
        std::vector<std::string> skills;
        std::string experience;

    public:
        Resume(const std::string& name, const std::vector<std::string>& skills,
               const std::string& experience)
            : name(name), skills(skills), experience(experience) {}

        const std::string& getName() const { return name; }
        const std::vector<std::string>& getSkills() const { return skills; }
        const std::string& getExperience() const { return experience; }

        bool operator==(const Resume& other) const {
            return name == other.name &&
                   skills == other.skills &&
                   experience == other.experience;
        }

        bool operator!=(const Resume& other) const { return !(*this == other); }
    };

    JobMarketplace() = default;

    void postJob(const std::string& title, const std::string& company,
                 const std::vector<std::string>& requirements) {
        jobListings.emplace_back(title, company, requirements);
    }

    void removeJob(const JobListing& job) {
        auto it = std::find(jobListings.begin(), jobListings.end(), job);
        if (it != jobListings.end())
            jobListings.erase(it);
    }

    void submitResume(const std::string& name, const std::vector<std::string>& skills,
                      const std::string& experience) {
        resumes.emplace_back(name, skills, experience);
    }

    void withdrawResume(const Resume& resume) {
        auto it = std::find(resumes.begin(), resumes.end(), resume);
        if (it != resumes.end())
            resumes.erase(it);
    }

    std::vector<JobListing> searchJobs(const std::string& skill) const {
        std::vector<JobListing> result;
        for (const auto& job : jobListings) {
            const auto& reqs = job.getRequirements();
            if (std::find(reqs.begin(), reqs.end(), skill) != reqs.end())
                result.push_back(job);
        }
        return result;
    }

    std::vector<Resume> getJobApplicants(const JobListing& job) const {
        const auto& reqs = job.getRequirements();
        std::vector<Resume> result;
        for (const auto& res : resumes) {
            if (matchesRequirements(res, reqs))
                result.push_back(res);
        }
        return result;
    }

    bool matchesRequirements(const Resume& resume, const std::vector<std::string>& requirements) const {
        const auto& skills = resume.getSkills();
        if (skills.size() != requirements.size())
            return false;
        // Check that all requirements are in skills (exact match)
        return std::all_of(requirements.begin(), requirements.end(),
                           [&skills](const std::string& req) {
                               return std::find(skills.begin(), skills.end(), req) != skills.end();
                           });
    }

    std::vector<JobListing>& getJobListings() { return jobListings; }
    const std::vector<JobListing>& getJobListings() const { return jobListings; }

    std::vector<Resume>& getResumes() { return resumes; }
    const std::vector<Resume>& getResumes() const { return resumes; }

private:
    std::vector<JobListing> jobListings;
    std::vector<Resume> resumes;
};

// Hash specializations for use in unordered containers (not required by the code, but matches Java's hashCode)
namespace std {
    template<>
    struct hash<JobMarketplace::JobListing> {
        size_t operator()(const JobMarketplace::JobListing& j) const {
            size_t h = hash<std::string>()(j.getTitle());
            h = h * 31 + hash<std::string>()(j.getCompany());
            for (const auto& r : j.getRequirements())
                h = h * 31 + hash<std::string>()(r);
            return h;
        }
    };

    template<>
    struct hash<JobMarketplace::Resume> {
        size_t operator()(const JobMarketplace::Resume& r) const {
            size_t h = hash<std::string>()(r.getName());
            for (const auto& s : r.getSkills())
                h = h * 31 + hash<std::string>()(s);
            h = h * 31 + hash<std::string>()(r.getExperience());
            return h;
        }
    };
}