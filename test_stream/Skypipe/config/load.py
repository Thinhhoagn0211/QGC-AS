class ConfigurationLoader:
    def __init__(self, config_path):
        self.config_path = config_path

    def load(self) -> dict:
        import yaml
        with open(self.config_path, 'r') as file:
            config = yaml.safe_load(file)
        return config