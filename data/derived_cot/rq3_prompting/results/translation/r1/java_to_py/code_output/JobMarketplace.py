class JobMarketplace:
    class JobListing:
        def __init__(self, title: str, company: str, requirements: list):
            self._title = title
            self._company = company
            self._requirements = requirements

        def get_title(self) -> str:
            return self._title

        def get_company(self) -> str:
            return self._company

        def get_requirements(self) -> list:
            return self._requirements

        def __eq__(self, other):
            if self is other:
                return True
            if type(self) != type(other):
                return False
            return (self._title == other._title and
                    self._company == other._company and
                    self._requirements == other._requirements)

        def __hash__(self):
            result = hash(self._title)
            result = 31 * result + hash(self._company)
            result = 31 * result + hash(tuple(self._requirements))
            return result

    class Resume:
        def __init__(self, name: str, skills: list, experience: str):
            self._name = name
            self._skills = skills
            self._experience = experience

        def get_name(self) -> str:
            return self._name

        def get_skills(self) -> list:
            return self._skills

        def get_experience(self) -> str:
            return self._experience

        def __eq__(self, other):
            if self is other:
                return True
            if type(self) != type(other):
                return False
            return (self._name == other._name and
                    self._skills == other._skills and
                    self._experience == other._experience)

        def __hash__(self):
            result = hash(self._name)
            result = 31 * result + hash(tuple(self._skills))
            result = 31 * result + hash(self._experience)
            return result

    def __init__(self):
        self._job_listings = []
        self._resumes = []

    def post_job(self, title: str, company: str, requirements: list):
        self._job_listings.append(JobMarketplace.JobListing(title, company, requirements))

    def remove_job(self, job: JobListing):
        self._job_listings.remove(job)

    def submit_resume(self, name: str, skills: list, experience: str):
        self._resumes.append(JobMarketplace.Resume(name, skills, experience))

    def withdraw_resume(self, resume: Resume):
        self._resumes.remove(resume)

    def search_jobs(self, skill: str) -> list:
        return [job for job in self._job_listings if skill in job.get_requirements()]

    def get_job_applicants(self, job: JobListing) -> list:
        return [resume for resume in self._resumes
                if self.matches_requirements(resume, job.get_requirements())]

    def matches_requirements(self, resume: Resume, requirements: list) -> bool:
        return (len(resume.get_skills()) == len(requirements) and
                all(skill in resume.get_skills() for skill in requirements))

    def get_job_listings(self) -> list:
        return self._job_listings

    def get_resumes(self) -> list:
        return self._resumes