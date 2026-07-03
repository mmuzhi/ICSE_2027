class JobMarketplace:
    def __init__(self):
        self.job_listings = []
        self.resumes = []

    def post_job(self, title, company, requirements):
        self.job_listings.append(JobListing(title, company, requirements))

    def remove_job(self, job):
        self.job_listings.remove(job)

    def submit_resume(self, name, skills, experience):
        self.resumes.append(Resume(name, skills, experience))

    def withdraw_resume(self, resume):
        self.resumes.remove(resume)

    def search_jobs(self, skill):
        return [job for job in self.job_listings if skill in job.requirements]

    def get_job_applicants(self, job):
        return [resume for resume in self.resumes if self.matches_requirements(resume, job.requirements)]

    @staticmethod
    def matches_requirements(resume, requirements):
        return len(resume.skills) == len(requirements) and all(skill in resume.skills for skill in requirements)

    class JobListing:
        def __init__(self, title, company, requirements):
            self.title = title
            self.company = company
            self.requirements = requirements

        def __eq__(self, other):
            if not isinstance(other, JobListing):
                return False
            return (self.title == other.title and 
                    self.company == other.company and 
                    self.requirements == other.requirements)

        def __hash__(self):
            return hash((self.title, self.company, tuple(self.requirements)))

    class Resume:
        def __init__(self, name, skills, experience):
            self.name = name
            self.skills = skills
            self.experience = experience

        def __eq__(self, other):
            if not isinstance(other, Resume):
                return False
            return (self.name == other.name and 
                    self.skills == other.skills and 
                    self.experience == other.experience)

        def __hash__(self):
            return hash((self.name, tuple(self.skills), self.experience))