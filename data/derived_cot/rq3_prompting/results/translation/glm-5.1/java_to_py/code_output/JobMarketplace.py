class JobMarketplace:
    class JobListing:
        def __init__(self, title, company, requirements):
            self.title = title
            self.company = company
            self.requirements = list(requirements)

        def get_title(self):
            return self.title

        def get_company(self):
            return self.company

        def get_requirements(self):
            return self.requirements

        def __eq__(self, other):
            if self is other:
                return True
            if other is None or not isinstance(other, JobMarketplace.JobListing):
                return False
            return (self.title == other.title and
                    self.company == other.company and
                    self.requirements == other.requirements)

        def __hash__(self):
            return hash((self.title, self.company, tuple(self.requirements)))

    class Resume:
        def __init__(self, name, skills, experience):
            self.name = name
            self.skills = list(skills)
            self.experience = experience

        def get_name(self):
            return self.name

        def get_skills(self):
            return self.skills

        def get_experience(self):
            return self.experience

        def __eq__(self, other):
            if self is other:
                return True
            if other is None or not isinstance(other, JobMarketplace.Resume):
                return False
            return (self.name == other.name and
                    self.skills == other.skills and
                    self.experience == other.experience)

        def __hash__(self):
            return hash((self.name, tuple(self.skills), self.experience))

    def __init__(self):
        self.job_listings = []
        self.resumes = []

    def post_job(self, title, company, requirements):
        self.job_listings.append(JobMarketplace.JobListing(title, company, requirements))

    def remove_job(self, job):
        self.job_listings.remove(job)

    def submit_resume(self, name, skills, experience):
        self.resumes.append(JobMarketplace.Resume(name, skills, experience))

    def withdraw_resume(self, resume):
        self.resumes.remove(resume)

    def search_jobs(self, skill):
        return [job for job in self.job_listings if skill in job.get_requirements()]

    def get_job_applicants(self, job):
        return [resume for resume in self.resumes
                if self.matches_requirements(resume, job.get_requirements())]

    def matches_requirements(self, resume, requirements):
        return (len(resume.get_skills()) == len(requirements) and
                all(r in resume.get_skills() for r in requirements))

    def get_job_listings(self):
        return self.job_listings

    def get_resumes(self):
        return self.resumes