class JobMarketplace:
    def __init__(self):
        self.job_listings = []
        self.resumes = []

    def post_job(self, title, company, requirements):
        self.job_listings.append(self.JobListing(title, company, requirements))

    def remove_job(self, job):
        if job in self.job_listings:
            self.job_listings.remove(job)

    def submit_resume(self, name, skills, experience):
        self.resumes.append(self.Resume(name, skills, experience))

    def withdraw_resume(self, resume):
        if resume in self.resumes:
            self.resumes.remove(resume)

    def search_jobs(self, skill):
        return [job for job in self.job_listings if skill in job.requirements]

    def get_job_applicants(self, job):
        return [resume for resume in self.resumes if self.matches_requirements(resume, job.requirements)]

    def matches_requirements(self, resume, requirements):
        if len(resume.skills) != len(requirements):
            return False
        for req in requirements:
            if req not in resume.skills:
                return False
        return True

    def get_job_listings(self):
        return self.job_listings

    def get_resumes(self):
        return self.resumes

    @staticmethod
    def _java_list_hash(lst):
        h = 1
        for item in lst:
            if item is None:
                h = 31 * h
            else:
                h = 31 * h + hash(item)
        return h

    class JobListing:
        def __init__(self, title, company, requirements):
            self.title = title
            self.company = company
            self.requirements = requirements

        def __eq__(self, other):
            if self is other:
                return True
            if type(other) is not type(self):
                return False
            return (self.title == other.title and 
                    self.company == other.company and 
                    self.requirements == other.requirements)

        def __hash__(self):
            result = hash(self.title)
            result = 31 * result + hash(self.company)
            result = 31 * result + JobMarketplace._java_list_hash(self.requirements)
            return result

    class Resume:
        def __init__(self, name, skills, experience):
            self.name = name
            self.skills = skills
            self.experience = experience

        def __eq__(self, other):
            if self is other:
                return True
            if type(other) is not type(self):
                return False
            return (self.name == other.name and 
                    self.skills == other.skills and 
                    self.experience == other.experience)

        def __hash__(self):
            result = hash(self.name)
            result = 31 * result + JobMarketplace._java_list_hash(self.skills)
            result = 31 * result + hash(self.experience)
            return result