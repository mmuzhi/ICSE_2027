#include <vector>
#include <string>
#include <algorithm>

class JobMarketplace {
public:
    class JobListing {
    private:
        std::string title;
        std::string company;
        std::vector<std::string> requirements;

    public:
        JobListing(std::string title, std::string company, std::vector<std::string> requirements)
            : title(std::move(title)), company(std::move(company)), requirements(std::move(requirements)) {}

        std::string getTitle() const { return title; }
        std::string getCompany() const { return company; }
        const std::vector<std::string>& getRequirements() const { return requirements; }

        bool operator==(const JobListing& that) const {
            return title == that.title && company == that.company && requirements == that.requirements;
        }
        bool operator!=(const JobListing& that) const { return !(*this == that); }

        int hashCode() const {
            int result = stringHashCode(title);
            result = 31 * result + stringHashCode(company);
            result = 31 * result + listHashCode(requirements);
            return result;
        }

    private:
        static int stringHashCode(const std::string& s) {
            int h = 0;
            for (char c : s) {
                h = 31 * h + static_cast<int>(c);
            }
            return h;
        }
        static int listHashCode(const std::vector<std::string>& list) {
            int h = 1;
            for (const auto& e : list) {
                h = 31 * h + stringHashCode(e);
            }
            return h;
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

        std::string getName() const { return name; }
        const std::vector<std::string>& getSkills() const { return skills; }
        std::string getExperience() const { return experience; }

        bool operator==(const Resume& that) const {
            return name == that.name && skills == that.skills && experience == that.experience;
        }
        bool operator!=(const Resume& that) const { return !(*this == that); }

        int hashCode() const {
            int result = stringHashCode(name);
            result = 31 * result + listHashCode(skills);
            result = 31 * result + stringHashCode(experience);
            return result;
        }

    private:
        static int stringHashCode(const std::string& s) {
            int h = 0;
            for (char c : s) {
                h = 31 * h + static_cast<int>(c);
            }
            return h;
        }
        static int listHashCode(const std::vector<std::string>& list) {
            int h = 1;
            for (const auto& e : list) {
                h = 31 * h + stringHashCode(e);
            }
            return h;
        }
    };

private:
    std::vector<JobListing> jobListings;
    std::vector<Resume> resumes;

    static bool contains(const std::vector<std::string>& list, const std::string& item) {
        return std::find(list.begin(), list.end(), item) != list.end();
    }

    static bool containsAll(const std::vector<std::string>& list, const std::vector<std::string>& items) {
        for (const auto& item : items) {
            if (!contains(list, item)) return false;
        }
        return true;
    }

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

    std::vector<JobListing> searchJobs(const std::string& skill) {
        std::vector<JobListing> result;
        for (const auto& job : jobListings) {
            if (contains(job.getRequirements(), skill)) {
                result.push_back(job);
            }
        }
        return result;
    }

    std::vector<Resume> getJobApplicants(const JobListing& job) {
        std::vector<Resume> result;
        for (const auto& resume : resumes) {
            if (matchesRequirements(resume, job.getRequirements())) {
                result.push_back(resume);
            }
        }
        return result;
    }

    bool matchesRequirements(const Resume& resume, const std::vector<std::string>& requirements) {
        return resume.getSkills().size() == requirements.size() && containsAll(resume.getSkills(), requirements);
    }

    std::vector<JobListing>& getJobListings() { return jobListings; }
    std::vector<Resume>& getResumes() { return resumes; }
};